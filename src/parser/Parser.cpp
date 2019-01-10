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
    while((curr=nextToken())!=nullptr
    && curr->type() == LEFT_PAREN) {
        curr = checkNext(SYMBOL_TOKEN, "command symbol is excepted!");
        cmd_parser = factory.getCommandParser(dynamic_cast<StrToken*>(curr)->value());
        // check
        if (cmd_parser == nullptr) {
            throw SemanticException("unsupported command!", curr->row(), curr->col());
        }
        
        cmd_parser->parse(*this);
    }
    if (curr == nullptr || curr->type() != EOF_TOKEN) {
        throw SemanticException("'(' is expected!", curr->row(), curr->col());
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

void Parser::mkApp() {
    if (!m_op_stack.empty()) {
        string op = m_op_stack.back();
        int arg_start = m_arg_scope_stack.back();

        m_arg_stack.erase(m_arg_stack.begin() + arg_start, m_arg_stack.end());

        m_arg_stack.push_back(op);
        m_arg_scope_stack.pop_back();
        m_op_stack.pop_back();
    }
}

void Parser::showEnv() {
    cout << "var environment: \n";
    int i = 0;
    for (auto item: m_var_stack) {
        cout << i++ << ": ";
        item->show();
        cout << endl;
    }
    for (auto item : m_scope_mark_stack) {
        cout << item << " ";
    }
    cout << endl;
    cout << endl;

    cout << "expr environment: \n";
    cout << "op stack: \n";
    for (auto item: m_op_stack) {
        cout << item << endl;
    }
    cout <<endl;
    cout << "arg stack: \n";
    i = 0;
    for (auto item: m_arg_stack) {
        cout << i++ << ": ";
        cout << item << endl;
    }
    for (auto item : m_arg_scope_stack) {
        cout << item << " ";
    }
    cout << endl;
    cout << endl;

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

    showEnv();
}