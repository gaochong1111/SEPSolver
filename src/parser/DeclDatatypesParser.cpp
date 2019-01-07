/*******************************************
*  @file  DeclDatatypesParser.cpp          *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "parser/DeclDatatypesParser.h"

extern SyntaxErrorTable SYNTAX_ERROR_INFO;

void DeclDatatypesParser::parse(Parser& parser) {
    parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    SortTypeList st_list;
    parseSortDeclList(parser, st_list);
    // parse datatype
    parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    parser.checkNext(LEFT_PAREN, SYNTAX_ERROR_INFO[LEFT_PAREN]);
    ConstructorDecList cd_list;
    parseConstructorDeclList(parser, cd_list);

    parser.checkNext(RIGHT_PAREN, SYNTAX_ERROR_INFO[RIGHT_PAREN]);

}