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
#include "solver/MonaExecutor.h"
#include "solver/MonaTranslator.h"
#include "component/Z3Buffer.h"
#include "Types.h"

extern z3::context z3_ctx;
extern Z3Buffer z3_buffer;

void SepSolver::solve() {
    cout << "solving ...\n"; 
    expr_vector free_items(z3_ctx);
    expr abs = m_problem->getAbsPhi(free_items);

    if (free_items.size() == 0) {
        // simple case
        MonaTranslator mona_tl(abs);
        mona_tl.writeToFile("test.mona");
        std::map<std::string, std::string> model;
        MonaExecutor mona_exe;
        mona_exe.setArgs("-q");
        mona_exe.setName("test.mona");
        std::cout << "execute mona -q test.mona\n";
        bool is_sat = mona_exe.execute(model);
        cout << "is_sat: " << is_sat << endl;
        if (is_sat) {
            for (auto kv : model) {
                cout << kv.first << " --> " << kv.second <<endl;
            }
        }

    } else {
        cout << "complex case;\n";
    }
}