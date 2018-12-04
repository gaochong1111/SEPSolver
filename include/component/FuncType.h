#if !defined(FUNC_TYPE_)
#define FUNC_TYPE_
/*******************************************
*  @file  FuncType.h                       * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

#include <vector>

#include "SortType.h"

using std::string;
using std::vector;


using ArgTypeList = vector<SortType>;


/*! @class FuncType
 *  @brief Brief class description
 *
 *  Detailed description
 */
class FuncType
{
public:
    FuncType() {}
    virtual ~FuncType() {}

protected:
    string m_name; ///< Member description
    ArgTypeList m_arg_list; ///< parameter list
    SortType m_ret_type; ///< return type
    string m_attr; ///< associate type
    bool m_determine; ///< arg_list whether determine
};


using ParTypeList = vector<string>;

/*! @class ParFuncType
 *  @brief Brief class description
 *
 *  Detailed description
 */
class ParFuncType :public FuncType
{
public:
    ParFuncType() {}
    virtual ~ParFuncType() {}

protected:
    ParTypeList m_par_type_list; ///< Member description
    string m_par_ret_type; ///< parametered return type
};

#endif
