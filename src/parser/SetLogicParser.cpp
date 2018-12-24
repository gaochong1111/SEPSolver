/*******************************************
*  @file  SetLogicParser.cpp               * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "parser/SetLogicParser.h"
#include "parser/LogicParser.h"
#include "parser/TheoryParser.h"
#include <iostream>

extern SyntaxErrorTable SYNTAX_ERROR_INFO;


using std::cout;
using std::endl;


/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @param parser Parameter description
 * @return Return parameter description
 */
void SetLogicParser::parse(Parser& parser) {
    Token* curr = parser.checkNext(STRING_TOKEN, SYNTAX_ERROR_INFO[STRING_TOKEN]);
    //
    string logic = dynamic_cast<StrToken*>(curr)->value(); 

    cout << "logic: " <<  logic << endl;
    LogicParser logic_parser(logic);
    logic_parser.parse(parser);
    Theories& theories = logic_parser.getTheories();
    for (string theory : theories) {
        cout << "theory: " << theory << endl;
        TheoryParser theory_parser(theory);
        theory_parser.parse(parser);
    }

    curr = parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]); 
    // action: init context by logic file
    
    parser.show();
}
