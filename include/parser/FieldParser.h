#if !defined(FIELD_PARSER_)
#define FIELD_PARSER_
/*******************************************
*  @file  FieldParser.h                    * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "CommandParser.h"

/*! @class FieldParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class FieldParser: public CommandParser
{
public:
    FieldParser();
    virtual ~FieldParser();

protected:
    m_; ///< Member description
};

#endif
