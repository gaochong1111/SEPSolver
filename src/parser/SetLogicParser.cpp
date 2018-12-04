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
#include <iostream>


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
    Token* curr = parser.checkNext(STRING_TOKEN, "logic name is expected!");
    //
    cout << dynamic_cast<StrToken*>(curr)->value() << endl;
    delete curr;

    curr = parser.checkNext(RIGHT_PAREN, "')' is expected!"); 
    delete curr;
}
