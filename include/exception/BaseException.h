/*******************************************
*  @file  BaseException.h                      * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-12-3                     *
*                                          *
*******************************************/
#if !defined(BASE_EXCEPTION_)
#define BASE_EXCEPTION_

#include <exception>
#include <string>
#include <iostream>

using std::string;
using std::to_string;
using std::exception;

/*! @class BaseException
 *  @brief Brief class description
 *
 *  Detailed description
 */
class BaseException : public exception
{
public:
    BaseException(string prefix, string info, int row=-1, int col=-1)
        :m_prefix(prefix), m_info(info), m_row(row), m_col(col) 
    {}
    virtual ~BaseException() {}
    virtual const char* what() {
        if (m_row == -1) {
            m_what = (m_prefix + ": " + m_info);
        } else {
            m_what = (m_prefix + " (" + to_string(m_row) + ", " 
                    + to_string(m_col) + "): " + m_info);
        }

        return m_what.c_str(); 
    }

protected:
    string m_prefix;
    string m_info; ///< Member description
    int m_row;
    int m_col; 
private:
    string m_what;
};

#endif
