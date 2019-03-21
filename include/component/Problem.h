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
#include "solver/Graph.h"

class Problem;
class SepSolver;

#include "solver/SepSolver.h"


using HeapType = pair<SortType*, SortType*>;
using EdgeType = pair<pair<int, int>, int>;
using RelationMatrix = vector<vector<int>>;

class Problem {
public:
    Problem();
    virtual ~Problem() {if (m_pred != nullptr) delete m_pred;}
    void setPredicate(Predicate* pred) {m_pred = pred;}
    void setPhi(z3::expr& phi);
    void setPsi(z3::expr& psi);

    void setSolver(SepSolver* ss);

    void setHeap(SortType* src, SortType* dst) {m_heap.first = src; m_heap.second = dst;}

    expr getAbsPhi(expr_vector& free_items);
    expr getAbsPsi(expr_vector& free_items);

    void initRm();
    void computeEqClass();

    void constructPhiGraph(Graph& g);
    void constructPsiGraph(Graph& g);

    bool checkAllocatingPlans(Graph& g_phi, Graph& g_psi);
    bool matchGraph(Graph& omega, Graph& g_psi);
    bool matchPto(expr& psi_atom, expr& omega_atom);
    bool _matchPredicate(expr& psi_atom, vector<int>& path);
    bool matchPredicate(expr& psi_atom, vector<int>& path);

    bool isSat();

    void show();
    void showEqClass();
    void showRM();
    void printPhi(Graph& g_phi, string fname);


protected:
    expr getSpatialAbs(expr& atom, int i, expr_vector& new_bools, expr_vector& free_items);
    expr getSpatialStar(expr_vector& new_bools);
    expr getAbs(expr_vector& free_items, expr& phi);

    void _constructPhiGraph(Graph& g, RelationMatrix& rm);
    void _computeEqClass(RelationMatrix& rm, vector<int>& loc_eq, vector<set<int>>& eq_class);
    void atomToEdge(expr& atom, EdgeType& edge, vector<expr>& locations);

    void initInfo(expr& phi, vector<expr>& locations, RelationMatrix& rm);
    void initRm(expr& abs, vector<expr>& locations, RelationMatrix& rm, expr_vector& free_items);
    void initPhiAllocated();

    void getOmegaAbs(expr& omega_abs_i, Graph& omega_g_i, vector<int>& omega, expr& omega_abs_i1); // next omega
    bool nextOmega(vector<int>& curr, vector<int>& target);

    bool checkPsiPredEmpty(expr& psi_pred);

private:
    int getSuffixIdx(string& str);

protected:
    Predicate* m_pred;
    z3::expr m_phi;
    z3::expr m_psi;

    z3::expr m_abs_phi;
    expr_vector m_phi_free_items;
    z3::expr m_abs_psi;
    expr_vector m_psi_free_items;

    vector<expr> m_phi_location;
    vector<int> m_phi_location_eq_class;
    vector<set<int>> m_phi_eq_class;
    RelationMatrix m_phi_location_relation;
    vector<int> m_phi_space_allocated;

    vector<expr> m_psi_location;
    vector<int> m_psi_location_eq_class;
    vector<set<int>> m_psi_eq_class;
    RelationMatrix m_psi_location_relation;

    SepSolver* m_ss;
    HeapType m_heap;
    expr_vector m_new_vars;
    
    int m_counter;
};


#endif