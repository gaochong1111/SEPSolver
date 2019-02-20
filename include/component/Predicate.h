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

    bool getStrt(int& case_i, expr_vector& svars, expr_vector& strt_items);
    expr getTr();

    void show();

private:
    expr getDeltaP();
    expr getUnfoldDeltap2(expr_vector& svars);

    int getCard(expr& var, expr_vector& svars);
    void setMatrix(int (&matrix)[4][4], int i, int j, int val);
    bool floyd(int (&matrix)[4][4]);
    expr getIJExpr(int (&matrix)[4][4], int i, int j, expr_vector& svars);
    expr getIExpr(int i, expr_vector& svars);

protected:
    expr_vector m_pars;
    expr m_base_rule;
    expr m_rec_rule;
private:
    expr m_data;
    expr m_pto;
    expr m_rec_app;
    expr m_deltap;
};

#endif