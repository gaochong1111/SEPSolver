#if !defined(PROBLEM_)
#define PROBLEM_
/*******************************************
*  @file  Problem.h                        *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2019-2-18                     *
*                                          *
*******************************************/

#include "Predicate.h"
#include "z3++.h"
#include "component/SortType.h"

using HeapType = pair<SortType*, SortType*>;

class Problem {
public:
    Problem();
    virtual ~Problem() {if (m_pred != nullptr) delete m_pred;}
    void setPredicate(Predicate* pred) {m_pred = pred;}
    void setPhi(z3::expr& phi) {m_phi = phi;}
    void setPsi(z3::expr& psi) {m_psi = psi;}

    void setHeap(SortType* src, SortType* dst) {m_heap.first = src; m_heap.second = dst;}

    void show();
protected:
    Predicate* m_pred;
    z3::expr m_phi;
    z3::expr m_psi;
    HeapType m_heap;
};


#endif