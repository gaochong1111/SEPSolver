#if !defined(COMMAND_PARSER_BUFFER_)
#define COMMAND_PARSER_BUFFER_
/*******************************************
*  @file  CommandParserBuffer.h            * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include <map>

#include "CommandParser.h"
#include "parser/SetLogicParser.h"
#include "parser/DeclSortParser.h"
#include "parser/DeclDatatypesParser.h"

using std::map;
using std::string;

class CommandParser;

/*! @class CommandParserBuffer
 *  @brief Brief class description
 *
 *  Detailed description
 */
class CommandParserBuffer
{
public:
    CommandParserBuffer(); 
    virtual ~CommandParserBuffer(); 

    CommandParser* getCommandParser();

    DeclSortParser* getDeclSortParser();

    DeclDatatypesParser* getDeclDatatypesParser();

    SetLogicParser* getSetLogicParser();

protected:
    map<string, CommandParser*> m_buffer; ///< Member description
};


#endif
