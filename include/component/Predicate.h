#if !defined(PREDICATE_)
#define PREDICATE_
/******************************************
*  @file  Predicate.h                      *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2019-2-18                     *
*                                          *
*******************************************/

#include "z3++.h"

class Predicate {
public:
    Predicate(z3::expr_vector pars, z3::expr base, z3::expr rec)
        :m_pars(pars), m_base_rule(base), m_rec_rule(rec) {}

    
    void show();

protected:
    z3::expr_vector m_pars;
    z3::expr m_base_rule;
    z3::expr m_rec_rule;
};

#endif