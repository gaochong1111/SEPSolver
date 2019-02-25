/*******************************************
*  @file  DefineFunctionParser.cpp         *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "parser/DefineFunctionParser.h"
#include "component/Z3Buffer.h"
#include "component/Predicate.h"

extern SyntaxErrorTable SYNTAX_ERROR_INFO;
extern Z3Buffer z3_buffer; 
extern z3::context z3_ctx;

void DefineFunctionParser::parse(Parser& parser) {
    Token* curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string fname = dynamic_cast<StrToken*>(curr)->value();
    parseParameters(parser);

    FuncType* pf = new FuncType(fname);

    VarList vpars;
    parser.topVar(vpars);
    expr_vector pars(z3_ctx);
    for (auto par : vpars) {
        pars.push_back(z3_buffer.getVar(par));
        pf->addArg(par->getSort()->getName());
    }

    SortType* range = parseSort(parser);

    pf->addArg(range->getName());

    parser.addFunc(fname, pf);

    // parse body
    parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string or_op = dynamic_cast<StrToken*>(curr)->value();
    if (or_op != "or") {
        throw SemanticException("the body must be 'or' function!", curr->row(), curr->col());
    }
    
    // parser.showEnv();
    // base rule
    parseExpr(parser);

    expr base = parser.topArg();
    parser.popArg();

    parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string exists_op = dynamic_cast<StrToken*>(curr)->value();
    if (exists_op != "exists") {
        throw SemanticException("the rule must be exists function!", curr->row(), curr->col());
    }
    // recursive rule
    parseExists(parser);

    z3::expr rec = parser.topArg();
    parser.popArg();

    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);
    // action
    parser.popVar();

    // parser.showEnv();
    
    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);
    // action 
    parser.popVar();
    // parser.showEnv();

    // TODO generate predicate definition

    Predicate*  pred = new Predicate(pars, base, rec);

    parser.addPredicate(pred);
}
