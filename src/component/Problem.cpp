/*******************************************
*  @file  Problem.cpp                      *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2019-2-18                     *
*                                          *
*******************************************/

#include "component/Problem.h"
#include "component/Z3Buffer.h"
#include "Types.h"

extern z3::context z3_ctx;
extern Z3Buffer z3_buffer;

Problem::Problem():m_pred(nullptr), m_phi(z3_ctx), m_psi(z3_ctx) {}

expr Problem::getAbsPhi() {

    cout << "computing abs phi: \n";
    expr_vector data_items(z3_ctx);
    int num = m_phi.num_args();
    for (int i=0; i<num-1; i++) {
        string sort_name = m_phi.arg(i).arg(0).get_sort().to_string();
        if (sort_name == "SetInt" || sort_name == "Int") {
            data_items.push_back(m_phi.arg(i));
        } else {
            expr item1 = z3_ctx.int_const(m_phi.arg(i).arg(0).to_string().c_str());
            expr item2 = z3_ctx.int_const(m_phi.arg(i).arg(1).to_string().c_str());
            string fname = m_phi.arg(i).decl().name().str();
            if (fname == "=") {
                data_items.push_back(item1 == item2);
            } else {
                data_items.push_back(item1 != item2);
            }
        }
    }
    expr data_abs = mk_and(data_items);
    cout << "data_abs: " << data_abs <<endl;

    expr spatial = m_phi.arg(num-1);
    num = spatial.num_args();
    expr_vector spatial_abs_items(z3_ctx);
    expr_vector new_bools(z3_ctx);
    expr_vector new_vars(z3_ctx);
    for (int i=0; i<num; i++) {
        expr atom = spatial.arg(i);
        spatial_abs_items.push_back(getSpatialAbs(atom, i, new_bools, new_vars));
    }

    cout << "new_vars: " << new_vars <<endl;

    expr spatial_abs = mk_and(spatial_abs_items);

    expr spatial_star = getSpatialStar(new_bools);

    expr abs = data_abs && spatial_abs && spatial_star;

    // cout << "spatial_abs: " << spatial_abs <<endl;
    cout << "spatial_star: " << spatial_star <<endl;

    return z3_ctx.bool_val(true);
}

void Problem::show() {

    cout << "Heap: \n";
    cout << m_heap.first->getName() << " -> " << m_heap.second->getName() << endl;
    cout << "predicate: \n";
    // m_pred->show();

    cout << "phi: " << m_phi << endl;

    getAbsPhi();

    cout << "psi: " << m_psi << endl;
}

expr Problem::getSpatialAbs(expr& atom, int i, expr_vector& new_bools, expr_vector& new_vars) {
    ostringstream oss;
    string new_name;
    oss << atom.arg(0) << "_BOOL_" << i; 
    expr nbool = z3_ctx.bool_const(oss.str().c_str());
    new_bools.push_back(nbool);

    if (atom.decl().name().str() == "pto") {
        return nbool;
    } else {
        expr_vector bool_items(z3_ctx);
        bool_items.push_back(nbool);
        // unfold 0
        expr_vector items(z3_ctx);
        int num = atom.num_args();
        for (int i=0; i<num/2; i++) {
            if (atom.arg(i).get_sort().to_string() == "SetInt") {
                items.push_back(atom.arg(i) == atom.arg(i+num/2));
            } else {
                items.push_back(z3_ctx.int_const(atom.arg(i).to_string().c_str()) ==
                    z3_ctx.int_const(atom.arg(i+num/2).to_string().c_str()));
            }
        }
        expr unfold0 = !nbool && mk_and(items);
        // unfold 1
        expr_vector src_pars(z3_ctx);
        expr_vector dst_pars(z3_ctx);
        expr_vector& pars = m_pred->getPars();
        int idx = m_pred->getEinGamma();
        if (idx != -1) {
            src_pars.push_back(z3_ctx.int_const(pars[0].to_string().c_str()));
            src_pars.push_back(z3_ctx.int_const(pars[idx+1].to_string().c_str()));
            dst_pars.push_back(z3_ctx.int_const(atom.arg(0).to_string().c_str()));
            dst_pars.push_back(z3_ctx.int_const(atom.arg(idx+1).to_string().c_str()));
            string name = atom.arg(idx+1).to_string() + "_BOOL_" + to_string(i);
            expr nbool_idx = z3_ctx.bool_const(name.c_str());
            bool_items.push_back(nbool_idx);
            new_bools.push_back(nbool_idx);
        }
        for (unsigned j=0; j<pars.size(); j++) {
            if (pars[j].get_sort().to_string() == "SetInt") {
                src_pars.push_back(pars[j]);
                dst_pars.push_back(atom.arg(j));
            }
        }
        // bool_prefix
        expr bool_prefix = mk_and(bool_items);
        // unfold1
        expr unfold1 = bool_prefix && m_pred->getUnfold1().substitute(src_pars, dst_pars);
        // unfold2
        expr unfold2 = bool_prefix && m_pred->getUnfold2(new_vars).substitute(src_pars, dst_pars);

        cout << "unfold0: " << unfold0 <<endl;
        cout << "unfold1: " << unfold1 <<endl;

        // cout << "unfold2: " << unfold2 <<endl;


        return !(!unfold0 && !unfold1 && !unfold2);
    }
}

expr Problem::getSpatialStar(expr_vector& new_bools) {
    expr_vector items(z3_ctx);
    items.push_back(z3_ctx.bool_val(true));

    for (unsigned int i=0; i<new_bools.size(); i++) {
        for (unsigned int j=i+1; j<new_bools.size(); j++) {
            string name1 = new_bools[i].to_string();
            string name2 = new_bools[j].to_string();
            int idx1 = getSuffixIdx(name1);
            int idx2 = getSuffixIdx(name2);
            if (idx1 != idx2) {
                items.push_back(!(z3_ctx.int_const(name1.c_str()) == z3_ctx.int_const(name2.c_str()) 
                    && new_bools[i] && new_bools[j]));
            }
        }
    }
    return mk_and(items);
}

int Problem::getSuffixIdx(string& str) {
    int i = str.find("_BOOL_");
    string istr = str.substr(i+6, str.length()-i-6);
    str = str.substr(0, i);
    return stoi(istr);
}