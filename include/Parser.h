#if !defined(PARSER_)
#define PARSER_
/*******************************************
*  @file  Parser.h                         * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include <iostream>

/*! @class Parser
 *  @brief Brief class description
 *
 *  Detailed description
 */
class Parser
{
public:
    Parser();
    virtual ~Parser();
    void parse(istream& is);

protected:
    m_; ///< Member description
};

#endif
