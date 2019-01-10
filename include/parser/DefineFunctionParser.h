#if !defined(DEFINE_FUNCTION_PARSER_)
#define DEFINE_FUNCTION_PARSER_
/*******************************************
*  @file  DefineFunctionParser.h           * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "CommandParser.h"

/*! @class DefineFunctionParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class DefineFunctionParser: public CommandParser
{
public:
    DefineFunctionParser() {}
    virtual ~DefineFunctionParser() {}
    virtual void parse(Parser& parser);

};

#endif
