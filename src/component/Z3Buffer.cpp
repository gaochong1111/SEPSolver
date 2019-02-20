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

void Z3Buffer::show() {
    cout << "sort table: \n";
    for (auto kv : z3_sort_table) {
        cout << kv.first << " --> " << kv.second << endl;
    }
    cout << "function table: \n";
    for (auto kv : z3_fun_table) {
        cout << kv.first << " --> " << kv.second << endl;
    }
}