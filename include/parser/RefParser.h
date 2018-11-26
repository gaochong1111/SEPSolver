#if !defined(REF_PARSER_)
#define REF_PARSER_
/*******************************************
*  @file  RefParser.h                      * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "CommandParser.h"

/*! @class RefParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class RefParser: public CommandParser
{
public:
    RefParser();
    virtual ~RefParser();

protected:
    m_; ///< Member description
};


#endif
