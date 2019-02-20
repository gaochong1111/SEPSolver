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
#include "component/Z3Buffer.h"

extern SyntaxErrorTable SYNTAX_ERROR_INFO;
extern Z3Buffer z3_buffer;

void CheckSatParser::parse(Parser& parser) {
    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

    z3_buffer.setVarEnv(parser);

    SepSolver ss;
    Problem* problem = parser.getProblem();
    problem->show();
    ss.setProblem(problem);
    ss.solve();
}