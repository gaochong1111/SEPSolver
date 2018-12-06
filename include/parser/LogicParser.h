#if !defined(LOGIC_PARSER_)
#define LOGIC_PARSER_
/*******************************************
*  @file  LogicParser.h                    * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include <fstream>

#include "Parser.h"
#include "Types.h"

using std::istream;

extern SyntaxErrorTable SYNTAX_ERROR_INFO;


/*! @class LogicParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class LogicParser
{
public:
    LogicParser(string logic): m_logic(logic) {}
    virtual ~LogicParser() {}
    virtual void parse(Parser& parser) {
        ifstream fin;
        fin.open(m_prefix+m_logic, std::ios_base::binary);
        Scanner scanner(fin); 

        Token* curr = nullptr;
        // ( logic
        curr = scanner.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
        curr = scanner.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);

        if (dynamic_cast<StrToken*>(curr)->value() != "logic")
            throw SemanticException("'logic' command is expected!", curr->row(), curr->col());
        // :keyword info 
        while ( (curr = scanner.checkNext(KEYWORD_TOKEN, SYNTAX_ERROR_INFO[KEYWORD_TOKEN])) != nullptr) {
            string key = dynamic_cast<StrToken*>(curr)->value;
            if (key == "theories") {
                // :theories ()
                scanner.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
                while (  (curr = scanner.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN])) != nullptr ) {

                }
            } else {
                curr = scanner.nextToken();
            }
        }
    }

    protected:
    string m_logic; ///< Member description
    string m_prefix="C:/Users/jackchong/Work/Code/CPP/SEPSolver/samples/Logics/";
    TokenScannerFactory m_factory;
    
    LogicInfo m_info;
    Theories theories;
};

#endif
