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
    sel_dec.second = sort;
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
