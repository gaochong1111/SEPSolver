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

extern SyntaxErrorTable SYNTAX_ERROR_INFO;

void DefineFunctionParser::parse(Parser& parser) {
    Token* curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string fname = dynamic_cast<StrToken*>(curr)->value();
    parseParameters(parser);

    SortType* range = parseSort(parser);

    cout << "range: " << range->getName() << endl;

    FuncType* pf = new FuncType(fname);
    VarList vlist;
    parser.topVar(vlist);
    for (auto item : vlist) {
        pf->addArg(item->getName());
    }
    pf->addArg(range->getName());

    parser.addFunc(fname, pf);

    // parse body
    parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string or_op = dynamic_cast<StrToken*>(curr)->value();
    if (or_op != "or") {
        throw SemanticException("the body must be 'or' function!", curr->row(), curr->col());
    }
    
    parser.showEnv();
    parseExpr(parser);



    parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string exists_op = dynamic_cast<StrToken*>(curr)->value();
    if (exists_op != "exists") {
        throw SemanticException("the rule must be exists function!", curr->row(), curr->col());
    }

    parseExists(parser);

    parser.showEnv();

    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);
    // action
    parser.popVar();

    parser.showEnv();
    
    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);
    // action 
    parser.popVar();
    parser.showEnv();
    
}

