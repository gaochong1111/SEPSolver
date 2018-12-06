/*******************************************
*  @file  CommandParserFactory.cpp         * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "CommandParserFactory.h"

/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @param sign Parameter description
 * @return Return parameter description
 */
CommandParser* CommandParserFactory::getCommandParser(const string& sign) {
    
    if (sign == "set-logic") {
        return m_buffer.getSetLogicParser(); 
    }

    return nullptr;
}
