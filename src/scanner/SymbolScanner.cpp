/*******************************************
*  @file  SymbolScanner.cpp                * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "scanner/SymbolScanner.h"

/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @param scanner Parameter description
 * @return Return parameter description
 */
Token* SymbolScanner::scan(Scanner& scanner) {
    // assert (scanner.curr() == 'a' || '|')
    int line = scanner.line();
    int col = scanner.col();
    scanner.clearStrCache();

    bool simple = false;
    if (scanner.curr() != '|') {
        scanner.cache(scanner.curr());
        simple = true;
    }
    while (scanner.next()) {
        if ((simple && isspace(scanner.curr())) ||
               (!simple && scanner.curr() == '|')) {
            return new StrToken(SYMBOL_TOKEN, line, col, 
                    string(scanner.getCache().begin(), 
                        scanner.getCache().end()));
        } 
        scanner.cache(scanner.curr());
    }

    return new Token(EOF_TOKEN, line, col);
}
