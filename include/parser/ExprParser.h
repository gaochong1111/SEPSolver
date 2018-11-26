#if !defined(EXPR_PARSER_)
#define EXPR_PARSER_
/*******************************************
*  @file  ExprParser.h                     * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "CommandParser.h"

/*! @class ExprParser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class ExprParser: public CommandParser
{
public:
    ExprParser();
    virtual ~ExprParser();

protected:
    m_; ///< Member description
};

#endif
