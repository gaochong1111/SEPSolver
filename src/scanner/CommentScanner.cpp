/*******************************************
*  @file  CommentScanner.cpp               * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "scanner/CommentScanner.h"

/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @param scanner Parameter description
 * @return Return parameter description
 */
Token* CommentScanner::scan(Scanner& scanner) {
    // assert(scanner.curr() == ';')
    int line = scanner.line();
    int col = scanner.col();
    while(scanner.next()) {
        if (scanner.curr() == '\n') return new Token(NULL_TOKEN, line, col); 
    }
    return new Token(EOF_TOKEN, line, col);
}

