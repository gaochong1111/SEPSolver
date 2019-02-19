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

using namespace z3;

class Predicate {
public:
    Predicate(z3::expr_vector pars, z3::expr base, z3::expr rec);

    void getABC(expr_vector& alpha, expr_vector& beta, expr_vector& gamma);
    void getAlpha(expr_vector& alpha);
    void getBeta(expr_vector& beta);
    void getGamma(expr_vector& gamma);
    void getX(expr_vector& x);

    expr getDeltaP();

    void show();

protected:
    expr_vector m_pars;
    expr m_base_rule;
    expr m_rec_rule;
private:
    expr m_data;
    expr m_pto;
    expr m_rec_app;
};

#endif