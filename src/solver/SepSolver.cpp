/*******************************************
*  @file  SepSolver.cpp                    *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2019-2-18                     *
*                                          *
*******************************************/

#include "solver/SepSolver.h"
#include "component/Z3Buffer.h"
#include "solver/MonaExecutor.h"
#include "solver/MonaTranslator.h"
#include "solver/SatRqspa.h"
#include "Types.h"

extern z3::context z3_ctx;
extern Z3Buffer z3_buffer;

SepSolver::~SepSolver() {
    if (m_problem != nullptr) {
        delete m_problem;
    }
}

void SepSolver::setProblem(Problem* problem) {
    m_problem = problem;
    m_problem->setSolver(this);
}

void SepSolver::solve() {
    string result = "";
    if (m_problem->isSat()) {
        result = checkSat();
    } else {
        result = checkEntl();
    }
    cout << "result: " << result <<endl;
}


string SepSolver::checkSat() {
    expr_vector free_items(z3_ctx);
    expr abs = m_problem->getAbsPhi(free_items);

    return check(abs, free_items);
}

string SepSolver::check(expr& abs, expr_vector& free_items) {
    if (free_items.size() == 0) {
        // simple case
        MonaTranslator mona_tl(abs);
        mona_tl.writeToFile("test.mona");
        std::map<std::string, std::string> model;
        MonaExecutor mona_exe;
        mona_exe.setArgs("-q");
        mona_exe.setName("test.mona");
        // std::cout << "execute mona -q test.mona\n";
        bool is_sat = mona_exe.execute(model);
        // cout << "is_sat: " << is_sat << endl;
        if (is_sat) {
            return "SAT";
        }
        return "UNSAT";
    } else {
        cout << "complex case;\n";
        vector<expr> vars;
        Z3ExprSet bvars;
        Z3ExprSet fovars;
        Z3ExprSet sovars;
        z3_buffer.getBVars(abs, bvars);
        z3_buffer.getFoVars(abs, fovars);
        z3_buffer.getSoVars(abs, sovars);
        vars.insert(vars.end(), bvars.begin(), bvars.end());
        vars.insert(vars.end(), fovars.begin(), fovars.end());
        vars.insert(vars.end(), sovars.begin(), sovars.end());
        /*
        cout << "free_items:\n";
        for (int i=0; i<free_items.size(); i++) {
            cout << free_items[i] <<endl;
        }

        cout << "Var: ";
        for (auto e : vars) {
            cout << e << " ";
        }
        cout << endl;
        */

        int MAX_CTX = 1 << free_items.size();
        int ctx = MAX_CTX-1;

        while (ctx >= 0) {
            expr_vector dst(z3_ctx);
            expr_vector phi_count_items(z3_ctx);
            for (unsigned int i=0; i<free_items.size(); i++) {
                if (ctx & (1<<i)) {
                    // true
                    dst.push_back(z3_ctx.bool_val(true));
                    phi_count_items.push_back(free_items[i]); 
                } else {
                    // false
                    dst.push_back(z3_ctx.bool_val(false));
                    phi_count_items.push_back(!free_items[i]); 
                }
            }
            expr phi_core = abs.substitute(free_items, dst);

            expr phi_count = mk_and(phi_count_items);

            MonaTranslator mona_tl(phi_core);
            mona_tl.writeToFile("phi_core.mona");
            map<string, string> model;
            MonaExecutor mona_exe;
            mona_exe.setArgs("-q");
            mona_exe.setName("phi_core.mona");
            bool is_sat = mona_exe.execute(model);

            // cout << "ctx: " << ctx << " -- " << is_sat <<endl;
            if (is_sat) {
                mona_exe.setArgs("-w -u -q");
                mona_exe.setName("phi_core.mona");
                mona_exe.execute("phi_core.dfa");
                // construct PA
                SatRqspa rqspa("phi_core.dfa", phi_count);
                z3::check_result sat_res = rqspa.checkSat(vars, model);
                if (sat_res == z3::sat) {
                    return "SAT";
                } else {
                    cout << "UNSAT\n";
                }
            }
            ctx ++;
        }
        return "UNSAT";
    }
}


string SepSolver::checkEntl() {
    // check phi and psi is sat
    cout << "check entl....\n";
    expr_vector phi_free_items(z3_ctx);
    expr abs_phi = m_problem->getAbsPhi(phi_free_items);
    string phi_res = check(abs_phi, phi_free_items);
    if (phi_res == "UNSAT") return "UNSAT";
    expr_vector psi_free_items(z3_ctx);
    expr abs_psi = m_problem->getAbsPsi(psi_free_items);
    string psi_res = check(abs_psi, psi_free_items);
    if (psi_res == "UNSAT") return "SAT";
    // match
    m_problem->initRm();
    Graph g_phi;
    Graph g_psi;
    m_problem->constructPhiGraph(g_phi);
    m_problem->constructPsiGraph(g_psi);

    cout << "MATCHING....\n";
    bool res = m_problem->checkAllocatingPlans(g_phi, g_psi);

    if (res) {
        return "UNSAT";
    } else {
        return "SAT";
    }
}