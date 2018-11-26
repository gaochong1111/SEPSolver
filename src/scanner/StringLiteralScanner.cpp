/*******************************************
*  @file  StringLiteralScanner.cpp         * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "scanner/StringLiteralScanner.h"

/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @param scanner Parameter description
 * @return Return parameter description
 */
Token* StringLiteralScanner::scan(Scanner& scanner) {
    // assert (scanner.curr() == '"')
    int line = scanner.line();
    int col = scanner.col();
    scanner.clearStrCache();
    while (scanner.next()) {
        if (scanner.curr() == '"') {
            return new StrToken(STRING_TOKEN, line, col, 
                    string(scanner.getCache().begin(), scanner.getCache().end()));
        }
        scanner.cache(scanner.curr());
    }
    return new Token(EOF_TOKEN, line, col);
}
