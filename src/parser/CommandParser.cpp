/*******************************************
*  @file  CommandParser.cpp                *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "CommandParser.h"

extern SyntaxErrorTable SYNTAX_ERROR_INFO;

SortType* CommandParser::parseSortDecl(Parser& parser) {
    Token* curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string sort = dynamic_cast<StrToken*>(curr)->value();
    // int row = curr->row();
    // int col = curr->col();

    curr = parser.checkNext(INT_TOKEN, SYNTAX_ERROR_INFO[INT_TOKEN]);
    int snum = dynamic_cast<IntToken*>(curr)->value();

    curr = parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

    SortType* p_sort = new SortType(sort, snum);
    // parser.addSort(sort, p_sort, row, col);
    return p_sort;
}


void CommandParser::parseSortDeclList(Parser& parser, SortTypeList& st_list) {
    // Token* curr = parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    Token* curr;
    while ((curr = parser.nextToken()) != nullptr 
                && curr->type() == LEFT_PAREN) {
        st_list.push_back(parseSortDecl(parser));
    }

    if (curr == nullptr || curr->type() != RIGHT_PAREN) {
        throw SyntaxException(SYNTAX_ERROR_INFO[RIGHT_PAREN], curr->row(), curr->col());
    }
}

void CommandParser::parseSelectorDecl(Parser& parser, SelectorDec& sel_dec) {
    Token* curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string key = dynamic_cast<StrToken*>(curr)->value();

    curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string sort = dynamic_cast<StrToken*>(curr)->value();

    curr = parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

    sel_dec.first = key;
    sel_dec.second = parser.getSort(sort);
}


void CommandParser::parseSelectorDeclList(Parser& parser, SelectorDecList& sd_list) {
    // Token* curr = parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    Token* curr;
    while((curr = parser.nextToken()) != nullptr 
    && curr->type() == LEFT_PAREN) {
        SelectorDec sd;
        parseSelectorDecl(parser, sd);
        sd_list.push_back(sd);
    }

    if (curr == nullptr || curr->type() != RIGHT_PAREN) {
        throw SyntaxException(SYNTAX_ERROR_INFO[RIGHT_PAREN], curr->row(), curr->col());
    }
}

void CommandParser::parseConstructorDecl(Parser& parser, ConstructorDec& con_dec) {
    Token* curr;
    curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    
    string key = dynamic_cast<StrToken*>(curr)->value();

    SelectorDecList sd_list;
    parseSelectorDeclList(parser, sd_list);

    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

    con_dec.first = key;
    con_dec.second = sd_list;
}

void CommandParser::parseConstructorDeclList(Parser& parser, ConstructorDecList& cd_list) {
    Token* curr;
    while ((curr = parser.nextToken()) != nullptr 
    && curr->type() == LEFT_PAREN) {
        ConstructorDec cd;
        parseConstructorDecl(parser, cd);
        cd_list.push_back(cd);
    }

    if (curr == nullptr || curr->type() != RIGHT_PAREN) {
        throw SyntaxException(SYNTAX_ERROR_INFO[RIGHT_PAREN], curr->row(), curr->col());
    }
}

SortType* CommandParser::parseSort(Parser& parser) {
    Token* curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string sort = dynamic_cast<StrToken*>(curr)->value();
    SortType* sort_ptr = parser.getSort(sort);
    if (sort_ptr == nullptr) {
        throw SemanticException("sort '" + sort + "' not defined!", curr->row(), curr->col());
    }
    return sort_ptr; 
}

void CommandParser::parseParameters(Parser& parser) {
    Token* curr = parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    parser.addVarScope();
    while ((curr = parser.nextToken()) != nullptr
    && curr->type() == LEFT_PAREN) {
        curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
        string pname = dynamic_cast<StrToken*>(curr)->value();
        SortType* sort = parseSort(parser);
        parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);
        // action
        Var* pa = new Var(pname, sort);
        parser.addVar(pa);
    }
}

void CommandParser::_parseExpr(Parser& parser) {
    Token* curr = parser.checkNext(SYMBOL_TOKEN, SYNTAX_ERROR_INFO[SYMBOL_TOKEN]);
    string op = dynamic_cast<StrToken*>(curr)->value();
    FuncType* pf =  parser.getFunc(op);
    if (pf != nullptr) {
        cout << "found function: "; pf->show(); cout << endl;
    } else {
        cout << "not supported op: " << op << endl;
    }

    parser.pushOp(op);
    Var* pv;
    string key;
    while ((curr = parser.nextToken()) != nullptr) {
        switch (curr->type()) {
            case LEFT_PAREN:
                m_paren_counter ++;
                _parseExpr(parser);
                break;
            case RIGHT_PAREN:
                m_paren_counter --;
                parser.mkApp();
                break;
            case INT_TOKEN:
                key = "int";
                pv = new Var("INT", parser.getSort(key));
                parser.pushArg(pv);
                break;
            case FLOAT_TOKEN:
                key = "float";
                pv = new Var("FLOAT", parser.getSort(key));
                parser.pushArg(pv);
                break;
            case SYMBOL_TOKEN:
            {
                string id = dynamic_cast<StrToken*>(curr)->value();
                Var* pv = parser.getVar(id);
                if (pv != nullptr) {
                    cout << "found var: "; pv->show(); cout <<endl;
                } else {
                    cout << "not found var: " << id << endl;
                }
                parser.pushArg(pv);
                break;
            }
            default:
                throw SemanticException("the argument is not valid!", curr->row(), curr->col());
        }

        if (m_paren_counter == 0) break;
    }
}

void CommandParser::parseExpr(Parser& parser) {
    parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    m_paren_counter = 1;
    _parseExpr(parser);
}

void CommandParser::parseExists(Parser& parser) {
    parseParameters(parser);

    parseExpr(parser);
    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

}

