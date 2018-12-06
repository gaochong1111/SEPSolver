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

