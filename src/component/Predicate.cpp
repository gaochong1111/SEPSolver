#include "component/Predicate.h"
#include "component/Z3Buffer.h"
#include "Types.h"


extern z3::context z3_ctx;
extern Z3Buffer z3_buffer;

Predicate::Predicate(z3::expr_vector pars, z3::expr base, z3::expr rec)
        :m_pars(pars), m_base_rule(base), m_rec_rule(rec), 
        m_data(z3_ctx), m_pto(z3_ctx), m_rec_app(z3_ctx), 
        m_deltap(z3_ctx), m_succ(z3_ctx), m_succ_pars(z3_ctx),
        m_tr(z3_ctx) {
    expr_vector x(z3_ctx);
    getX(x);
    expr body = m_rec_rule.body().substitute(x);

    int num = body.num_args();
    expr_vector data_items(z3_ctx);
    for (int i=0; i<num-1; i++) {
        data_items.push_back(body.arg(i));
    }
    m_data = mk_and(data_items);

    expr sep_app = body.arg(num-1);
    m_pto = sep_app.arg(0);
    m_rec_app = sep_app.arg(1);

    m_deltap = getDeltaP();

    initSucc();

    m_tr = getTr();
}

void Predicate::getABC(expr_vector& alpha, expr_vector& beta, expr_vector& gamma) {

}

void Predicate::getAlpha(expr_vector& alpha) {
    for (unsigned int i=1; i<m_pars.size()/2; i++) {
        alpha.push_back(m_pars[i]);
    }
}

void Predicate::getBeta(expr_vector& beta) {
    for (unsigned int i=m_pars.size()/2+1; i<m_pars.size(); i++) {
        beta.push_back(m_pars[i]);
    }
}

void Predicate::getGamma(expr_vector& gamma) {
    int num = m_rec_app.num_args();
    for (int i=1; i < num/2; i++) {
        gamma.push_back(m_rec_app.arg(i));
    }
}

void Predicate::getX(expr_vector& x) {
    Z3_context ctx = Z3_context(z3_ctx);
    Z3_ast rec = Z3_ast(m_rec_rule);
    int n = Z3_get_quantifier_num_bound(ctx, rec);
    for (int i=n-1; i>=0; i--) {
        Z3_symbol name = Z3_get_quantifier_bound_name(ctx, rec, i);
        Z3_sort sort = Z3_get_quantifier_bound_sort(ctx, rec, i);
        Z3_ast t = Z3_mk_const(ctx, name, sort);
        x.push_back(to_expr(z3_ctx, t));
    }
}

expr Predicate::getDeltaP() {
    expr_vector src_vars(z3_ctx);
    expr_vector dst_vars(z3_ctx);
    int num = m_rec_app.num_args();
    for (int i=num/2-1; i>=1; i++) {
        if (m_rec_app.arg(i).get_sort().name().str() == "SetInt") {
            src_vars.push_back(m_rec_app.arg(i));
            dst_vars.push_back(m_pars[i+num/2]);
        } else {
            break;
        }
    }
    return m_data.substitute(src_vars, dst_vars);
}

expr Predicate::getUnfold1() {
    if (m_tr.hash() == z3_ctx.bool_val(false).hash()) return z3_ctx.bool_val(false);
    if (getEinGamma() != -1) {
        return !(z3_ctx.int_const((m_pars[0].to_string().c_str())) == 
            z3_ctx.int_const((m_pars[m_pars.size()/2].to_string().c_str()))) && m_deltap; 
    }
    return m_deltap;
}

expr Predicate::getUnfold2(expr_vector& new_vars) {
    if (m_tr.hash() == z3_ctx.bool_val(false).hash()) return z3_ctx.bool_val(false);
    expr_vector gamma(z3_ctx);
    getGamma(gamma);
    int idx = getEinGamma();
    expr_vector items(z3_ctx);
    if (idx != -1) {
       string name1 = newName(gamma[idx].to_string(), new_vars.size());
       new_vars.push_back(z3_ctx.int_const(name1.c_str()));
       string name2 = newName(gamma[idx].to_string(), new_vars.size());
       new_vars.push_back(z3_ctx.int_const(name2.c_str()));
       
       expr E = z3_ctx.int_const((m_pars[0].to_string().c_str()));
       items.push_back(!(E == new_vars[0]));
       items.push_back(!(E == new_vars[1]));
    } 
    expr_vector dt_alpha(z3_ctx);
    expr_vector dt_beta(z3_ctx);
    expr_vector gamma_1(z3_ctx);
    expr_vector gamma_2(z3_ctx);
    int num = m_pars.size();
    for (int i=1; i<num/2; i++) {
        if (m_pars[i].get_sort().to_string() == "SetInt") {
            dt_alpha.push_back(m_pars[i]);
            dt_beta.push_back(m_pars[i+num/2]);

            string name1 = newName(gamma[i-1].to_string(), new_vars.size());
            new_vars.push_back(z3_ctx.constant(name1.c_str(), m_pars[i].get_sort()));
            string name2 = newName(gamma[i-1].to_string(), new_vars.size());
            new_vars.push_back(z3_ctx.constant(name2.c_str(), m_pars[i].get_sort()));
            
            expr v1 = z3_ctx.constant(name1.c_str(), gamma[i-1].get_sort());
            expr v2 = z3_ctx.constant(name2.c_str(), gamma[i-1].get_sort());
            gamma_1.push_back(v1);
            gamma_2.push_back(v2);
        }
    }
    items.push_back(m_deltap.substitute(dt_beta, gamma_1));
    items.push_back(m_deltap.substitute(dt_alpha, gamma_2));
    items.push_back(m_deltap.substitute(dt_alpha, gamma_1).substitute(dt_beta, gamma_2));

    cout << "replace: " << m_deltap.substitute(dt_alpha, gamma_1).substitute(dt_beta, gamma_2) <<endl;

    // items.push_back(m_tr.substitute(dt_alpha, gamma_2));

    return mk_and(items);
}

int Predicate::getEinGamma() {
    expr_vector gamma(z3_ctx);
    getGamma(gamma);
    for (unsigned int i=0; i<gamma.size(); i++) {
        if (m_pars[0].hash() == gamma[i].hash()) {
            return i;
        }
    }
    return -1;
}

bool Predicate::getStrt(int& case_i, expr_vector& svars, expr_vector& strt_items) {
    expr deltap = getDeltaP();
    expr phi_r1 = deltap.arg(0);
    svars.push_back(phi_r1.arg(0));

    // case_i [00 00 0 b] [strict (max min), min or max, empty]
    case_i = 0; // (setunion S2 (min S1))

    int matrix[4][4]; // 0: min(S1) 1:min(S2) 2:max(S1) 3:max(S2)
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            matrix[i][j] = INT_MAX;
        }
    }

    if (phi_r1.arg(1).is_const()) {
        // (= S1 S2)
        svars.push_back(phi_r1.arg(1));
        // min(S1) = min(S2) max(S1)=max(S2)
        matrix[0][1] = 0;
        matrix[1][0] = 0;
        matrix[2][3] = 0;
        matrix[3][2] = 0;
        case_i = -1;
    } else {
        expr setu = phi_r1.arg(1);
        svars.push_back(setu.arg(0));
        if (setu.arg(1).decl().name().str() == "setunion") {
            // (setunion S1 (setunion (min S1) (max S1)))
            case_i = 5; // [xx 10 1]
        } else if (setu.arg(1).decl().name().str() == "MAX") {
            // (setunion S1 (max S1))
            case_i = 2; // [xx 01 x]
        }
    }

    bool has_s1 = false;
    bool has_s2 = false;

    for (unsigned int i=1; i<m_deltap.num_args(); i++) {
        expr phi_r2_i = m_deltap.arg(i);
        if (phi_r2_i.is_app()) {
            int c = 0;
            expr item1 = phi_r2_i.arg(0);
            expr item2 = phi_r2_i.arg(1);
            if (item2.is_app()) {
                if (item2.decl().name().str() == "+") {
                    c = item2.arg(1).get_numeral_int();
                    item2 = item2.arg(0);
                } else if (item2.decl().name().str() == "-") {
                    c = -item2.arg(1).get_numeral_int();
                    item2 = item2.arg(0);
                }
            }
            int row = getCard(item1, svars);
            int col = getCard(item2, svars);

            if (((row&1)&(col&1)) == 0) has_s1 = true;
            if (((row&1)|(col&1)) == 1) has_s2 = true;

            if (phi_r2_i.decl().name().str() == "=") {
                setMatrix(matrix, row, col, c);
                setMatrix(matrix, col, row, -c);
            } else if (phi_r2_i.decl().name().str() == "<=") {
                setMatrix(matrix, row, col, c);
            } else if (phi_r2_i.decl().name().str() == ">=") {
                setMatrix(matrix, col, row, -c);
            }
        }
    }
    if (has_s1) {
        // min(S1) <= max(S1)
        setMatrix(matrix, 0, 2, 0);
    }
    if (has_s2) {
        // min(S2) <= max(S2)
        setMatrix(matrix, 1, 3, 0);
        if (case_i != -1) {
            // s2 noempty
            case_i |= 1; // [xx xx 1]

            setMatrix(matrix, 0, 1, 0); // min(S1) <= min(S2)
            setMatrix(matrix, 3, 2, 0); // max(S2) <= max(S1)

            if ((case_i & 6) == 0) {
                // [xx 00 x]
                setMatrix(matrix, 2, 3, 0); // max(S1) <= max(S2)
            } else if ((case_i & 6) == 1) {
                // [xx 01 x]
                setMatrix(matrix, 1, 0, 0); // min(S2) <= min(S1)
            }
        } 
    }

    bool is_sat = floyd(matrix);

    if (is_sat) {
        if (matrix[0][1] < 0) {
            case_i |= 8; // min(S1) <= min(S2) - c (c > 0)
        }
        if (matrix[3][2] < 0) {
            case_i |= 16; // max(S2) <= max(S1) - c (c > 0)
        }

        // strict result
        for (int i=0; i<3; i++) {
            for (int j=i+1; j<4; j++) {
                strt_items.push_back(getIJExpr(matrix, i, j, svars));
            }
        }
    }
    return is_sat;
}


expr Predicate::getTr() {
    int case_i = 0;
    expr_vector svars(z3_ctx);
    expr_vector strt_items(z3_ctx);

    bool is_sat = getStrt(case_i, svars, strt_items);

    if (is_sat) {
        expr or_item1 = svars[0] == svars[1];
        expr or_item2 = m_deltap;
        // phi_r(2)
        expr or_item3 = getUnfoldDeltap2(svars);
        expr or_item4 = getUnfoldDeltap3(svars, strt_items);
        return !(!or_item1 && !or_item2 && !or_item3 && !or_item4); 
    } else {
        return z3_ctx.bool_val(false);
    }
}

void Predicate::initSucc() {
    expr_vector and_items(z3_ctx);
    expr S = z3_ctx.constant("S", z3_buffer.getSort("SetInt"));
    expr x = z3_ctx.int_const("x");
    expr y = z3_ctx.int_const("y");
    m_succ_pars.push_back(S);
    m_succ_pars.push_back(x);
    m_succ_pars.push_back(y);

    and_items.push_back(z3_buffer.getBelongsto(x, S));
    and_items.push_back(z3_buffer.getBelongsto(y, S));
    expr_vector pars(z3_ctx);
    expr z = z3_ctx.int_const("z");
    pars.push_back(z);
    expr ebody = z3_buffer.getBelongsto(z, S) 
        && !(z >= x + 1 && y >= z + 1);
    and_items.push_back(forall(pars, ebody));
    m_succ = mk_and(and_items);
}

void Predicate::show() {

    cout << "pars: \n";
    for (unsigned int i=0; i<m_pars.size(); i++) {
        cout << m_pars[i] << " ";
    }
    cout << endl;

    cout << "base: " << m_base_rule << endl;
    cout << "rec: " << m_rec_rule << endl;

    // z3_buffer.show();

    cout << "Details: \n";
    expr_vector x(z3_ctx);
    getX(x);
    expr_vector rx(z3_ctx);
    for (unsigned int i=0; i<x.size(); i++) {
        cout << x[i] << " ";
    }
    cout << endl;

    cout << "pto: " << m_pto <<endl;
    cout << "recursive app: " << m_rec_app <<endl;
    cout << "data formula: " << m_data << endl;

    expr_vector alpha(z3_ctx);
    getAlpha(alpha);
    expr_vector beta(z3_ctx);
    getBeta(beta);
    expr_vector gamma(z3_ctx);
    getGamma(gamma);
    
    cout <<"alpha: " << alpha << endl;
    cout << "beta: " << beta << endl;
    cout << "gamma: " << gamma << endl;

    cout << "deltaP: " << m_deltap <<endl;

    expr_vector svars(z3_ctx);
    expr_vector strt_items(z3_ctx);
    int case_i = 0;
    bool is_sat = getStrt(case_i, svars, strt_items);
    cout << "is_sat: " << is_sat << endl;
    cout << "case_i: " << case_i << endl;
    cout << "strt: " << strt_items << endl;
    
    cout << "tr closure: \n";
    expr tr = getTr();
    cout << tr <<endl;
}


expr Predicate::getUnfoldDeltap2(expr_vector& svars) {
    expr_vector evars(z3_ctx);
    expr nvar = z3_ctx.constant("ES", z3_buffer.getSort("SetInt"));
    evars.push_back(nvar);
    expr_vector vars1(z3_ctx);
    vars1.push_back(svars[0]);
    expr_vector vars2(z3_ctx);
    vars2.push_back(svars[1]);
    return exists(evars, m_deltap.substitute(vars1, evars) 
        && m_deltap.substitute(vars2, evars));
}

expr Predicate::getUnfoldDeltap3(expr_vector& svars, expr_vector& strt_items) {
    expr_vector evars(z3_ctx);
    expr nvar1 = z3_ctx.constant("ES1", z3_buffer.getSort("SetInt"));
    expr nvar2 = z3_ctx.constant("ES2", z3_buffer.getSort("SetInt"));
    expr nvar3 = z3_ctx.constant("ES3", z3_buffer.getSort("SetInt"));
    evars.push_back(nvar1);
    evars.push_back(nvar2);

    expr_vector svars1(z3_ctx);
    svars1.push_back(svars[0]);
    expr_vector dvars1(z3_ctx);
    dvars1.push_back(nvar1); 

    expr_vector svars2(z3_ctx);
    svars2.push_back(svars[1]);
    expr_vector  dvars2(z3_ctx);
    dvars2.push_back(nvar2);

    //
    expr phi_r = m_deltap.arg(0) && strt_items[0] && strt_items[1] 
        && strt_items[4] && strt_items[5];
    expr_vector and_items(z3_ctx);
    and_items.push_back(phi_r.substitute(svars2, dvars1));
    and_items.push_back(phi_r.substitute(svars1, dvars2));
    expr emptyset = z3_buffer.getEmptyset();
    expr setminus = z3_buffer.getSetminus(nvar1, nvar2);

    and_items.push_back(nvar3 == setminus);

    and_items.push_back(!(nvar2 == emptyset));
    and_items.push_back(!(nvar3 == emptyset));
    and_items.push_back(z3_buffer.getSubset(nvar2, nvar1));
    and_items.push_back(z3_buffer.getMax(nvar3) <= z3_buffer.getMin(nvar2) - 1);

    expr min_s2 = z3_buffer.getMin(nvar2);
    expr set_item = z3_buffer.getSet(min_s2);
    expr union_item = z3_buffer.getSetunion(nvar3, set_item);
    expr_vector epars(z3_ctx);
    expr x = z3_ctx.int_const("x");
    expr y = z3_ctx.int_const("y");
    epars.push_back(x);
    epars.push_back(y);

    expr_vector dvars(z3_ctx);
    dvars.push_back(union_item);
    dvars.push_back(x);
    dvars.push_back(y);

    expr succ_item = m_succ.substitute(m_succ_pars, dvars);

    expr_vector spars(z3_ctx);
    expr S1 = svars[0];
    expr S2 = svars[1];
    spars.push_back(z3_buffer.getMin(S1));
    spars.push_back(z3_buffer.getMin(S2));

    // imply
    expr ebody = !(succ_item && !strt_items[0].substitute(spars, epars));
    and_items.push_back(forall(epars, ebody));

    return !forall(evars, !mk_and(and_items));
}

int Predicate::getCard(expr& item, expr_vector& svars) {
    int index = 0;
    if (item.decl().name().str() == "max") {
        index += 2;
    }

    if (item.arg(0).hash() == svars[1].hash()) {
        index += 1;
    }
    return index;
}

void Predicate::setMatrix(int (&matrix)[4][4], int i, int j, int val) {
    if (matrix[i][j] > val) {
        matrix[i][j] = val;
    }
}

bool Predicate::floyd(int (&matrix)[4][4]) {

    int path[4][4];
    int dist[4][4];

    // init path and dist
    for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++){
                    path[i][j] = j;
                    dist[i][j] = matrix[i][j];
            }
    }

    // compute the shortest path
    int tmp;
    for (int i=0; i<4; i++) {
            for (int row=0; row<4; row++) {
                    for (int col=0; col<4; col++) {
                            tmp = (dist[row][i] == INT_MAX || dist[i][col]==INT_MAX)? INT_MAX : dist[row][i] + dist[i][col];
                            if (dist[row][col] > tmp) {
                                    dist[row][col] = tmp;
                                    path[row][col] = path[row][i];
                            }
                    }
            }
    }

    // check whether negative cycle exists or not
    for (int i=0; i<4; i++) {
            for (int row=0; row<4; row++) {
                    for (int col=0; col<4; col++) {
                            tmp = (dist[row][i] == INT_MAX || dist[i][col]==INT_MAX)? INT_MAX : dist[row][i] + dist[i][col];
                            if (dist[row][col] > tmp) {
                                    return false;
                            }
                    }
            }
    }

    for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++){
                    matrix[i][j] = dist[i][j];
            }
    }
    return true;
}

expr Predicate::getIJExpr(int (&matrix)[4][4], int i, int j, expr_vector& svars) {
    expr phi_ij = z3_ctx.bool_val(true);
    if (i != j) {
        if (matrix[i][j] != INT_MAX && -matrix[i][j] == matrix[j][i]) {
            if (matrix[i][j] < 0) {
                phi_ij = getIExpr(j, svars) == getIExpr(i, svars) + z3_ctx.int_val(-matrix[i][j]);
            } else {
                phi_ij = getIExpr(i, svars) == getIExpr(j, svars) + z3_ctx.int_val(matrix[i][j]);
            }
        } else {
            if (matrix[i][j] != INT_MAX) {
                if (matrix[i][j] < 0) {
                    phi_ij = getIExpr(j, svars) >= getIExpr(i, svars) + z3_ctx.int_val(-matrix[i][j]);
                } else {
                    phi_ij = getIExpr(i, svars) <= getIExpr(j, svars) + z3_ctx.int_val(matrix[i][j]);
                }
            }
            if (matrix[j][i] != INT_MAX) {
                if (matrix[j][i] < 0) {
                    phi_ij = getIExpr(i, svars) >= getIExpr(j, svars) + z3_ctx.int_val(-matrix[j][i]);
                } else {
                    phi_ij = getIExpr(j, svars) <= getIExpr(i, svars) + z3_ctx.int_val(matrix[j][i]);
                }
            }
        }
    }
    return phi_ij;
}

expr Predicate::getIExpr(int i, expr_vector& svars) {
    string key = "_SetInt_Int";
    if ((i&2) == 0) {
        key = "min" + key;
    } else {
        key = "max" + key;
    }
    func_decl f = z3_buffer.getFuncDecl(key);
    return f(svars[i&1]);
}


string Predicate::newName(string name, int i) {
    return name.replace(name.find("?"), 1, "") + "_N" + to_string(i);
}