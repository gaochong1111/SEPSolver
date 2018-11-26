/*******************************************
*  @file  TokenScannerFactory.cpp          * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "TokenScannerFactory.h"

/*! @brief Build TokenScanner
 *
 *  Detailed description
 *
 * @param sign The first character of Token
 * @return Return the TokenScanner 
 */
TokenScanner* TokenScannerFactory::getTokenScanner(char sign) {
    switch(sign) {
        case '(':
            return new LeftParenScanner(); 
        case ')':
            return new RightParenScanner();
        case '0':
        case '-':
            return new NumberLiteralScanner();
        case '|':
        case 'a':
            return new SymbolScanner();
        case '"':
            return new StringLiteralScanner();
        case ';':
            return new CommentScanner();
        case ':':
            return new KeywordScanner();
        default:
            return new TokenScanner();

    }
    
}
