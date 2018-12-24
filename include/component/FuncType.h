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

#include "component/SortType.h"
#include <iostream>
#include <vector>
#include <set>

using std::string;
using std::vector;
using std::set;
using std::cout;
using std::endl;

using ArgTypeList = vector<SortType*>;
using ParTypeList = vector<string>;
using ParTypeSet = set<string>;

/*! @class FuncType
 *  @brief Brief class description
 *
 *  Detailed description
 */
class FuncType
{
public:
    FuncType(string name, string attr="", bool determine=true)
        :m_name(name), m_attr(attr), m_determine(determine){}
    virtual void addArg(string arg) {m_arg_list.push_back(arg);}
    virtual void addPar(string par) {}
    void setAttr(string attr) {m_attr = attr;}
    virtual ~FuncType() {}

    virtual int determine(ArgTypeList& arg_type_list) {
        // TODO
        return 0;
    }

    virtual void show() {
        cout << "func: " << m_name << " ";
        cout << " (";
        for (auto arg : m_arg_list) {
            cout << arg <<  " ";
        }
        cout << " <-ret) ";
        cout << "(attr: " << m_attr << ") ";
    }

protected:
    string m_name; ///< Member description
    ParTypeList m_arg_list; ///< parameter list
    string m_attr; ///< associate type
    bool m_determine; ///< arg_list whether determine
};



/*! @class ParFuncType
 *  @brief Brief class description
 *
 *  Detailed description
 */
class ParFuncType :public FuncType
{
public:
    ParFuncType(string name):FuncType(name, "", false) {}
    virtual ~ParFuncType() {}
    virtual void addPar(string par) {m_par_set.insert(par);}
    virtual void addArg(string arg) {
        m_arg_list.push_back(arg);
        if (m_par_set.find(arg) != m_par_set.end()) {
            m_par_arg_mark_list.push_back(true);
        } else {
            m_par_arg_mark_list.push_back(false);
        }
    }

    virtual void show() {
        FuncType::show();
        cout << " parameters <";
        for (auto par : m_par_arg_mark_list) {
            cout << par << " ";
        }
        cout << "> ";
    }

protected:
    ParTypeSet m_par_set; ///< Member description
    vector<bool> m_par_arg_mark_list; ///< mark the same position argument
};

#endif
