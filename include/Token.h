#if !defined(TOKEN_H_)
#define TOKEN_H_

#include <string>
using std::string;

/*****************************************
*  @file     Token.h                       *
*  @brief    Token Definition              *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
******************************************/
enum TOKEN
{
	NULL_TOKEN = 0,
	LEFT_PAREN,///< ( 
	RIGHT_PAREN, ///< )
	KEYWORD_TOKEN, ///< key word 
	SYMBOL_TOKEN, ///< id 
	STRING_TOKEN, ///< constant string 
	INT_TOKEN, ///< constant int 
	FLOAT_TOKEN, ///< constant float 
	BV_TOKEN, ///< bit vector 
	EOF_TOKEN ///< EOF 
};


class Token {
public:
    TOKEN type;
    int row;
    int col;
};

class StrToken: public Token {
public:
    string value;
};

class FloatToken: public Token {
public:
        float value;
};

class IntToken: public Token {
public:
    int value;
};


#endif
