/*******************************************
*  @file  AssertParser.cpp                 *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "parser/AssertParser.h"

extern SyntaxErrorTable SYNTAX_ERROR_INFO;

void AssertParser::parse(Parser& parser) {
    parseExpr(parser);

    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

    // action

}