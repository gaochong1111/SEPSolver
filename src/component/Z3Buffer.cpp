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
    if (z3_sort_table.find(pst) == z3_sort_table.end()) {
        z3_sort_table.insert(pair<SortType*, sort>(pst, pst->operator z3::sort()));
    }
    return z3_sort_table.at(pst);
}

expr& Z3Buffer::getVar(Var* pvar) {
    if (z3_var_table.find(pvar) == z3_var_table.end()) {
        z3_var_table.insert(pair<Var*, expr>(pvar, pvar->operator z3::expr()));
    }
    return z3_var_table.at(pvar);
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