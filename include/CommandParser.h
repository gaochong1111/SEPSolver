#if !defined(COMMAND_PARSER_)
#define COMMAND_PARSER_
/*******************************************
*  @file  CommandParser.h                  * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "Parser.h"

class Parser;

/*! @class CommandParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class CommandParser
{
public:
    CommandParser() {}
    virtual ~CommandParser() {}
    virtual void parse(Parser& parser) {}

};
#endif
