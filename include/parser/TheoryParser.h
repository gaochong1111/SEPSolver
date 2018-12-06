#if !defined(THEORY_PARSER_)
#define THEORY_PARSER_
/*******************************************
*  @file  TheoryParser.h                   * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/

#include "CommandParser.h"

/*! @class TheoryParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class TheoryParser : public CommandParser
{
public:
    TheoryParser() {}
    virtual ~TheoryParser() {}
    virtual parse(Parser& parser);

protected:
    Scanner m_scanner;

};

#endif
