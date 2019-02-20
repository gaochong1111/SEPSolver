/*******************************************
*  @file  Z3Buffer.cpp                     *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "component/Z3Buffer.h"

extern z3::context z3_ctx;

void Z3Buffer::init(Parser& parser) {

    for (auto kv : parser.m_sort_table) {
        z3_sort_table.insert(pair<string, sort>(kv.first, kv.second->operator z3::sort()));
    }

    for (auto kv : parser.m_func_table) {
        if (kv.second->isDetermine()) {
            ostringstream oss;
            oss << kv.second->getName();
            ArgTypeList arg_list;
            ParTypeList& parg_list = kv.second->getArgList();
            for (auto item : parg_list) {
                oss << "_" << item;
                arg_list.push_back(parser.getSort(item));
            }
            arg_list.pop_back();
            string key = oss.str();
            z3_fun_table.insert(pair<string, func_decl>(key, kv.second->determine(arg_list)));
        }
    }

    z3_var_table.insert(pair<string, expr>("emptyset", z3_ctx.constant("emptyset", z3_sort_table.at("SetInt"))));
}

void Z3Buffer::setVarEnv(Parser& parser) {
    for (auto v : parser.m_var_stack) {
        m_var_env.push_back(getVar(v));
    }
}

sort& Z3Buffer::getSort(SortType* pst) {
    string key = pst->getName();
    if (z3_sort_table.find(key) == z3_sort_table.end()) {
        z3_sort_table.insert(pair<string, sort>(key, pst->operator z3::sort()));
    }
    return z3_sort_table.at(key);
}

sort Z3Buffer::getSort(string key) {
    if (z3_sort_table.find(key) == z3_sort_table.end()) {
        return sort(z3_ctx);
    }
    return z3_sort_table.at(key);
}

expr& Z3Buffer::getVar(Var* pvar) {
    string key = pvar->getName() + "&" + pvar->getSort()->getName();
    if (z3_var_table.find(key) == z3_var_table.end()) {
        z3_var_table.insert(pair<string, expr>(key, pvar->operator z3::expr()));
    }
    return z3_var_table.at(key);
}

func_decl Z3Buffer::getFuncDecl(FuncType* pft, ArgTypeList& arg_type_list, Parser& parser) {
    ostringstream oss;
    oss << pft->getName();
    for (auto item : arg_type_list) {
        oss << "_" << item->getName();
    }
    oss << "_" <<pft->getRange();

    string key = oss.str();
    if (z3_fun_table.find(key) == z3_fun_table.end()) {
        z3_fun_table.insert(pair<string, func_decl>(key, pft->determine(arg_type_list)));
    }
    return z3_fun_table.at(key);
}

func_decl Z3Buffer::getFuncDecl(string key) {
    if (z3_fun_table.find(key) == z3_fun_table.end()) {
        return func_decl(z3_ctx);
    }
    return z3_fun_table.at(key);
}

expr Z3Buffer::getEmptyset() {
    return z3_var_table.at("emptyset"); 
}

expr Z3Buffer::getSetinterset(expr& S1, expr& S2) {
    func_decl setinterset = z3_fun_table.at("setintersect_SetInt_SetInt_SetInt");
    expr_vector args(z3_ctx);
    args.push_back(S1);
    args.push_back(S2);
    return setinterset(args);
}

expr Z3Buffer::getSetunion(expr& S1, expr& S2) {
    func_decl setunion = z3_fun_table.at("setunion_SetInt_SetInt_SetInt");
    expr_vector args(z3_ctx);
    args.push_back(S1);
    args.push_back(S2);
    return setunion(args);
}

expr Z3Buffer::getSet(expr& i) {
    func_decl setd = z3_fun_table.at("set_Int_SetInt");
    expr_vector args(z3_ctx);
    args.push_back(i);
    return setd(args);
}

expr Z3Buffer::getSetminus(expr& S1, expr& S2) {
    func_decl setminus = z3_fun_table.at("setminus_SetInt_SetInt_SetInt");
    expr_vector args(z3_ctx);
    args.push_back(S1);
    args.push_back(S2);
    return setminus(args);
}


expr Z3Buffer::getSubset(expr& S1, expr& S2) {
    func_decl subset = z3_fun_table.at("subset_SetInt_SetInt_Bool");

    expr_vector args(z3_ctx);
    args.push_back(S1);
    args.push_back(S2);
    return subset(args);
}

expr Z3Buffer::getBelongsto(expr& i, expr& S) {
    func_decl belongsto = z3_fun_table.at("belongsto_Int_SetInt_Bool");

    expr_vector args(z3_ctx);
    args.push_back(i);
    args.push_back(S);
    return belongsto(args);
}

expr Z3Buffer::getMax(expr& S) {
    func_decl max_f = z3_fun_table.at("max_SetInt_Int");

    expr_vector args(z3_ctx);
    args.push_back(S);
    return max_f(args);
}

expr Z3Buffer::getMin(expr& S) {
    func_decl min_f = z3_fun_table.at("min_SetInt_Int");

    expr_vector args(z3_ctx);
    args.push_back(S);
    return min_f(args);
}

void Z3Buffer::show() {
    cout << "var table: \n";
    for (auto kv : z3_var_table) {
        cout << kv.first << " --> " << kv.second <<endl;
    }
    cout <<endl;
    cout << "sort table: \n";
    for (auto kv : z3_sort_table) {
        cout << kv.first << " --> " << kv.second << endl;
    }
    cout <<endl;
    cout << "function table: \n";
    for (auto kv : z3_fun_table) {
        cout << kv.first << " --> " << kv.second << endl;
    }
    cout << endl;

    cout << "var env: \n";
    for (auto v : m_var_env) {
        cout << v << "  ";
    }
    cout << endl;
}
