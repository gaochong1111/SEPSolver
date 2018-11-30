#if !defined(PARSER_)
#define PARSER_
/*******************************************
*  @file  Parser.h                         * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include <iostream>
#include <map>
#include <vector>
#include "Scanner.h"

using std::map;
using std::vector;
using std::string;

using SortTable = map<string, SortType>; 
using FuncTable = map<string, FuncType>;
using VarStack = vector<Var>;
using ScopeMarkStack = vector<int>;

/*! @class Parser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class Parser
{
public:
    Parser(istream& is) :m_scanner(is) {}
    virtual ~Parser() {}
    void parse();
    Scanner& getScanner() const {return m_scanner;}

protected:
    Scanner m_scanner; ///< scanner
    SortTable m_sort_table; ///< global sort table
    FuncTable m_func_table; ///< global function table

    VarStack m_var_stack; ///< var environment
    ScopeMarkStack m_scope_mark_stack; ///< scope mark

};

#endif
