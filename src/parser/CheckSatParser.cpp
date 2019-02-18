/*******************************************
*  @file  CheckSatParser.cpp               *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2019-2-18                     *
*                                          *
*******************************************/

#include "parser/CheckSatParser.h"
#include "solver/SepSolver.h"

extern SyntaxErrorTable SYNTAX_ERROR_INFO;

void CheckSatParser::parse(Parser& parser) {
    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

    SepSolver ss;
    Problem* problem = parser.getProblem();
    problem->show();
    ss.setProblem(problem);
    ss.solve();
}