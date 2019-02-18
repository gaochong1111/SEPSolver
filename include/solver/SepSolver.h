#if !defined(SEPSOLVER_)
#define SEPSOLVER_
/*******************************************
*  @file  SepSolver.h                      *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2019-2-18                     *
*                                          *
*******************************************/

#include "component/Problem.h"

class SepSolver {
public:
    SepSolver() {}
    virtual ~SepSolver() {}
    void setProblem(Problem* problem) {m_problem = problem;}

    void solve();


protected:
    Problem* m_problem;
};

#endif