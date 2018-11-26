#if !defined(EXISTS_PARSER_)
#define EXISTS_PARSER_

/*******************************************
*  @file  ExistsParser.h                   * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "CommandParser.h"

/*! @class ExistsParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class ExistsParser: public CommandParser
{
public:
    ExistsParser();
    virtual ~ExistsParser();

protected:
    m_; ///< Member description
};
#endif
