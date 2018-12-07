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
#include "Types.h"
#include "Scanner.h"
#include "TokenScannerFactory.h"
#include "exception/SemanticException.h"
#include "exception/SyntaxException.h"
#include "component/FuncType.h"
#include "component/SortType.h"
#include "component/Var.h"

using std::map;
using std::vector;
using std::string;

/*! @class Parser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class Parser
{
public:
    Parser(istream& is, TokenScannerFactory& factory) :m_scanner(is), m_factory(factory) {}
    virtual ~Parser() {}
    void parse();
    void skip() {m_scanner.skip();}
    Scanner& getScanner() {return m_scanner;}
    TokenScannerFactory& getFactory() {return m_factory;}

    Token* checkNext(TOKEN type, string info) {return m_scanner.checkNext(type, info);}

protected:
    Scanner m_scanner; ///< scanner
    TokenScannerFactory& m_factory; ///< factory
    SortTable m_sort_table; ///< global sort table
    FuncTable m_func_table; ///< global function table

    VarStack m_var_stack; ///< var environment
    ScopeMarkStack m_scope_mark_stack; ///< scope mark

};

#endif
