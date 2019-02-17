#if !defined(Z3BUFFER_)
#define Z3BUFFER_
/*******************************************
*  @file  Z3Buffer.h                       *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2019-2-17                     *
*                                          *
*******************************************/

#include "z3++.h"
#include "Var.h"
#include "SortType.h"
#include "FuncType.h"
#include <map>
#include "Parser.h"

using namespace z3;
using std::map;

class Z3Buffer {
public:
    Z3Buffer() {}

    sort& getSort(SortType* pst) {
        if (z3_sort_table.find(pst) == z3_sort_table.end()) {
            z3_sort_table.at(pst) = pst->operator z3::sort();
        }
        return z3_sort_table.at(pst);
    }

    expr& getVar(Var* pvar) {
        if (z3_var_table.find(pvar) == z3_var_table.end()) {
            z3_var_table.at(pvar) = pvar->operator z3::expr();
        }
        return z3_var_table.at(pvar);
    }


    func_decl getFuncDecl(FuncType* pft, ArgTypeList& arg_type_list, Parser& parser) {
        ostringstream oss;
        oss << pft->getName();
        for (auto item : arg_type_list) {
            oss << "_" << item->getName();
        }
        oss << pft->getRange();

        string key = oss.str();
        if (z3_fun_table.find(key) == z3_fun_table.end()) {
            z3_fun_table.at(key) = pft->determine(arg_type_list, parser);
        }
        return z3_fun_table.at(key);
    }

protected:
    map<SortType*, sort> z3_sort_table;
    map<Var*, expr> z3_var_table;
    map<string, func_decl> z3_fun_table; 
};


#endif