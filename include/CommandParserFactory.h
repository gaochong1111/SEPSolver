/*******************************************
*  @file  CommandParserFactory.h           * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "CommandParser.h"


/*! @class CommandParserFactory
 *  @brief Brief class description
 *
 *  Detailed description
 */
class CommandParserFactory
{
public:
    CommandParserFactory() {}
    virtual ~CommandParserFactory() {}
    CommandParser* getCommandParser(const string& sign); 
};
