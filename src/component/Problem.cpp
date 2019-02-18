/*******************************************
*  @file  Problem.cpp                      *
*  @brief  Brief file description          *
*                                          *
*  @author   Chong Gao                     *
*  @version  1.0                           *
*  @date     2019-2-18                     *
*                                          *
*******************************************/

#include "component/Problem.h"
#include "Types.h"

extern z3::context z3_ctx;

Problem::Problem():m_pred(nullptr), m_phi(z3_ctx), m_psi(z3_ctx) {}

void Problem::show() {

    cout << "Heap: \n";
    cout << m_heap.first->getName() << " -> " << m_heap.second->getName() << endl;
    cout << "predicate: \n";
    m_pred->show();

    cout << "phi: " << m_phi << endl;

    cout << "psi: " << m_psi << endl;
}