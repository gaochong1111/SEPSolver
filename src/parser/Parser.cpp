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
    while((curr=checkNext(LEFT_PAREN, "'(' is expected!"))!=nullptr && curr->type()
            == LEFT_PAREN) {

        delete curr;
        curr = checkNext(SYMBOL_TOKEN, "command symbol is excepted!");
        cmd_parser = factory.getCommandParser(dynamic_cast<StrToken*>(curr)->value());
        // check
        if (cmd_parser == nullptr) {
            throw SemanticException("unsupported command!", curr->row(), curr->col());
        }
        delete curr;
        
        cmd_parser->parse(*this);
    }
    if (curr != nullptr)
        delete curr;
}

/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @param type Parameter description
 * @param info Parameter description
 * @return Return parameter description
 */
Token* Parser::checkNext(TOKEN type, string info) {
    TokenScanner* ts = nullptr;
    Token* result = nullptr;
    char sign = 0; 
    if (m_scanner.skip()) {
        sign = TokenScanner::id(m_scanner.curr());
        ts = m_factory.getTokenScanner(sign);
        result = ts->scan(m_scanner);
        
        if (result->type() != type)
            throw SyntaxException(info, result->row(), result->col());

        delete ts;
        return result;
    }

    return nullptr;
}
