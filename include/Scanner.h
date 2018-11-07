#if !defined(SCANNER_H_)
#define SCANNER_H_H

#include<iostream>
#include "Token.h"

/*******************************************
*  @file     Scanner.h                     *
*  @brief    Scanner for smt file          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

class Scanner {
public:
    Scanner(){}
    ~Scanner(){}
    Token* scan();

protected:
    void next();
    void initNormalizedTable();
    
    void readComment();
    Token* readSymbol();
    Token* readQuotedSymbol();
    Token* readBvLiteral();
    Token* readNumberLiteral();
    Token* readSignedNumberOrSymbol();
    Token* readStringLiteral();

protected:
    int line; ///< line number
    int position; ///< position in line
    char curr; ///< current char
    char normalizedTable[256]; ///< normalized table for characters
};
#endif
