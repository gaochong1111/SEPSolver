/*******************************************
*  @file  NumberLiteralScanner.cpp         * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include "scanner/NumberLiteralScanner.h"


/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @param scanner Parameter description
 * @return Return parameter description
 */
Token* NumberLiteralScanner::scan(Scanner& scanner) {
    // assert(scanner.curr() == '0' || '-')
    int line = scanner.line();
    int col = scanner.col();
    scanner.clearStrCache();
    scanner.cache(scanner.curr());
    int what = 0; // 0: int, 1: float, -1: symbol
    while(scanner.next()) {
        if (stop(scanner.curr())) {
            break;
        } else if (scanner.curr() == '.') {
            if (what == 0) {
                what = 1;
            } else if (what == 1) {
                what = -1;
            }
        } else if (!isdigit(scanner.curr())) {
            what = -1;
        } 
        scanner.cache(scanner.curr());
    }

    if (scanner.iseof()) 
        return new Token(EOF_TOKEN, line, col);

    scanner.back(-1); 

    if (scanner.getCache().size() == 1) what = -1;
    
    if (what == 0) {
        return new IntToken(INT_TOKEN, line, col,
                std::stoi(string(scanner.getCache().begin(), 
                        scanner.getCache().end())));
    } else if (what == 1) {
        return new FloatToken(FLOAT_TOKEN, line, col,
                std::stof(string(scanner.getCache().begin(),
                        scanner.getCache().end())));
    } else {
        return new StrToken(SYMBOL_TOKEN, line, col,
                string(scanner.getCache().begin(), 
                    scanner.getCache().end()));
    }
}

/*! @brief Brief function description here
 *
 *  Detailed description
 *
 * @param curr Parameter description
 * @return Return parameter description
 */
bool NumberLiteralScanner::stop(char curr) {
    set<char> stopset;
    stopset.insert(' ');
    stopset.insert(')');
    stopset.insert('(');
    stopset.insert('\n');
    return stopset.find(m_normalized_table[static_cast<int>(curr)]) != stopset.end();   
}
