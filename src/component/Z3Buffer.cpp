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

sort& Z3Buffer::getSort(SortType* pst) {
    string key = pst->getName();
    if (z3_sort_table.find(key) == z3_sort_table.end()) {
        z3_sort_table.insert(pair<string, sort>(key, pst->operator z3::sort()));
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
    oss << pft->getRange();

    string key = oss.str();
    if (z3_fun_table.find(key) == z3_fun_table.end()) {
        z3_fun_table.insert(pair<string, func_decl>(key, pft->determine(arg_type_list, parser)));
    }
    return z3_fun_table.at(key);
}