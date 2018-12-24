/*******************************************
*  @file  Parser.cpp                       * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "Parser.h"
#include "Types.h"
#include "CommandParserFactory.h"


extern SyntaxErrorTable SYNTAX_ERROR_INFO;

/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @return Return parameter description
 */
void Parser::parse() {
    // parse ( and symbol
    CommandParserFactory factory;
    CommandParser* cmd_parser;
    Token* curr = nullptr;
    while((curr=checkNext(LEFT_PAREN,SYNTAX_ERROR_INFO[LEFT_PAREN]))!=nullptr) {
        curr = checkNext(SYMBOL_TOKEN, "command symbol is excepted!");
        cmd_parser = factory.getCommandParser(dynamic_cast<StrToken*>(curr)->value());
        // check
        if (cmd_parser == nullptr) {
            throw SemanticException("unsupported command!", curr->row(), curr->col());
        }
        
        cmd_parser->parse(*this);
    }
}


void Parser::addSort(string key, SortType* value, int row, int col) {
    if (m_sort_table.find(key) != m_sort_table.end()) {
        throw SemanticException("Redefined sort!", row, col); 
    }
    m_sort_table[key] = value;
}

void Parser::addFunc(string key, FuncType* value, int row, int col) {
    if (m_func_table.find(key) != m_func_table.end()) {
        throw SemanticException("Redefined function!", row, col); 
    }
    m_func_table[key] = value;
}


void Parser::show() {
    cout << "supported sort: \n";
    for (auto item : m_sort_table) {
        cout << item.first << " ";
    }
    cout << endl;
    cout << "supported func: \n";
    for (auto item: m_func_table) {
        item.second->show();
        cout << endl;
    }
    cout << endl;
}