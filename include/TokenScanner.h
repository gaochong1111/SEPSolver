#if !defined(TOKEN_SCANNER_)
#define TOKEN_SCANNER_
/*******************************************
*  @file  TokenScanner.h                   * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-8                     *
*                                          *
*******************************************/
#include "Scanner.h"
#include "Token.h"
#include <cctype>

/*! @class TokenScanner
 *  @brief Base class of all token scanners
 *
 *  Detailed description
 */
class TokenScanner
{
public:
    TokenScanner() {}
    virtual ~TokenScanner() {}
    virtual Token* scan(Scanner& scanner) {return new Token(NULL_TOKEN, scanner.line(), scanner.col());}
    
public:
    static void initNormalizedTable();
    static char id(char ch) {return m_normalized_table[static_cast<int>(ch)];}

protected:
    static char m_normalized_table[256]; ///< normalized table for characters
};

#endif
