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
#include "z3++.h"

extern SyntaxErrorTable SYNTAX_ERROR_INFO;

void AssertParser::parse(Parser& parser) {
    parseExpr(parser);

    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

    // action
    z3::expr phi = parser.topArg();
    parser.popArg();

    if (phi.is_app() && phi.decl().name().str() == "not") {
        expr psi = phi.arg(0);
        parser.addPsi(psi);
    } else {
        parser.addPhi(phi);
    }

}