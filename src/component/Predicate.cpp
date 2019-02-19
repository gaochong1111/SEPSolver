#include "component/Predicate.h"
#include "Types.h"

extern z3::context z3_ctx;

Predicate::Predicate(z3::expr_vector pars, z3::expr base, z3::expr rec)
        :m_pars(pars), m_base_rule(base), m_rec_rule(rec), 
        m_data(z3_ctx), m_pto(z3_ctx), m_rec_app(z3_ctx){
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

void Predicate::show() {

    cout << "pars: \n";
    for (unsigned int i=0; i<m_pars.size(); i++) {
        cout << m_pars[i] << " ";
    }
    cout << endl;

    cout << "base: " << m_base_rule << endl;
    cout << "rec: " << m_rec_rule << endl;

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

    cout << "deltaP: " << getDeltaP() <<endl;
}