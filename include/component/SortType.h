#if !defined(SORT_TYPE_)
#define SORT_TYPE_
/*******************************************
*  @file  SortType.h                       * 
*  @brief    Brief file description        *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2018-11-7                     *
*                                          *
*******************************************/

using std::string;

/*! @class SortType
 *  @brief Brief class description
 *
 *  Detailed description
 */
class SortType
{
public:
    SortType(string sort_name, int sort_size)
        : m_sort_name(sort_name), m_sort_size(sort_size) {}
    virtual ~SortType() {}

protected:
    string m_sort_name; ///< Member description
    int m_sort_size; ///< sort size
};


#endif
