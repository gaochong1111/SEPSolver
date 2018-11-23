#if !defined(TOKEN_H_)
#define TOKEN_H_

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


/*! @class Token 
 *  @brief Brief class description
 *
 *  Detailed description
 */
class Token {

private:
    TOKEN m_type;
    int m_row;
    int m_col;

public:
    Token(TOKEN type, int row, int col)
        : m_type(type), m_row(row), m_col(col) {}
    virtual ~Token() {}
    TOKEN type() const {return m_type;}
    int row() const {return m_row;}
    int col() const {return m_col;}
};


/*! @class StrToken 
 *  @brief Brief class description
 *
 *  Detailed description
 */
class StrToken: public Token {

private:
    string m_value;

public:
    StrToken(TOKEN type, int row, int col, string value)
        : Token(type, row, col), m_value(value) {}

    string& value() const {return m_value;}
    virtual ~StrToken() {}
};


/*! @class FloatToken 
 *  @brief Brief class description
 *
 *  Detailed description
 */
class FloatToken: public Token {

private:
    float m_value;

public:
    FloatToken(TOKEN type, int row, int col, float value)
        : Token(type, row, col), m_value(value) {}
    float value() const {return m_value;}
    virtual ~FloatToken() {}
};


/*! @class IntToken 
 *  @brief Brief class description
 *
 *  Detailed description
 */
class IntToken: public Token {

private:
    int m_value;

public:
    IntToken(TOKEN type, int row, int col, int value)
        : Token(type, row, col), m_value(value) {}
    int value() const {return m_value;}
    virtual ~IntToken() {}
};

#endif
