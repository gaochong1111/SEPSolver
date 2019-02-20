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

    sort& getSort(SortType* pst); 

    void init(Parser& parser);

    void setVarEnv(Parser& parser);
    vector<expr>& getVarEnv() {return m_var_env;}

    expr& getVar(Var* pvar);

    func_decl getFuncDecl(FuncType* pft, ArgTypeList& arg_type_list, Parser& parser);
    func_decl getFuncDecl(string key);
    sort getSort(string key);

    expr getEmptyset();
    expr getSetinterset(expr& S1, expr& S2);
    expr getSetunion(expr& S1, expr& S2);
    expr getSet(expr& i);
    expr getSetminus(expr& S1, expr& S2);
    expr getSubset(expr& S1, expr& S2);
    expr getBelongsto(expr& i, expr& S);
    expr getMax(expr& S);
    expr getMin(expr& S);

    void show();

protected:
    map<string, sort> z3_sort_table;
    map<string, expr> z3_var_table;
    map<string, func_decl> z3_fun_table; 

    vector<expr> m_var_env;
};


#endif