#if !defined(SREF_PARSER_)
#define SREF_PARSER_
/*******************************************
*  @file  SrefParser.h                     * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "CommandParser.h"

/*! @class SrefParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class SrefParser: public CommandParser
{
public:
    SrefParser();
    virtual ~SrefParser();

protected:
    m_; ///< Member description
};
#endif
