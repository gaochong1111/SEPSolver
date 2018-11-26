#if !defined(PTO_PARSER_)
#define PTO_PARSER_
/*******************************************
*  @file  PtoParser.h                      * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "CommandParser.h"

/*! @class PtoParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class PtoParser: public CommandParser
{
public:
    PtoParser();
    virtual ~PtoParser();

protected:
    m_; ///< Member description
};
#endif
