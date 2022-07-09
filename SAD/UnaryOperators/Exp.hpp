#ifndef ExpOp_H
#define ExpOp_H

#include <cmath> 

#include<SAD/Expression.hpp>
#include<SAD/UnaryOperators/Negation.hpp>



namespace sad{

template<typename numType>
class Exp_expr: public AbstractExpression<numType>{ 
    public:
    Exp_expr(const Expression<numType> &expr):expr(expr){}
    friend class Expression<numType>;
    private:
    Expression<numType> expr;
    Expression<numType> derivative(const unsigned int &wrt)const{
        if(expr.is_ZERO()){return ZERO<numType>;}
        return  expr.derivative(wrt)*exp(expr);
    }
    numType evaluate(const map<IDType,numType> &at)const{return std::exp(expr.evaluate(at));}
    bool is_CONST()const{return expr.is_CONST();}
    string str()const{return string("exp") + string("(") + print_expr(expr) + string(")");}
    string head()const{return string("exp");}
    Expression<numType> subExpr()const{return expr;}
};
template<typename numType>
class Exp_num: public AbstractExpression<numType>{ 
    public:
    Exp_num(const numType &expr):expr(expr){}
    friend class Expression<numType>;
    private:
    numType expr;
    Expression<numType> derivative(const unsigned int &wrt)const{return  ZERO<numType>;}
    numType evaluate(const map<IDType,numType> &at)const{return std::exp(expr);}
    bool is_CONST()const{return true;}
    string str()const{return string("exp") + string("(") + print_expr(expr) + string(")");}
    string head()const{return string("exp");}
    Expression<numType> subExpr()const{return expr;}
    };
template<typename numType> Expression<numType> exp(const Expression<numType> &expr){
    if(expr.head() == "log"){return expr.subExpr();}
    return AbsExp_ptr<numType>(new Exp_expr<numType>(expr)); 
}
template<typename numType> Expression<numType> exp(const numType &x){return AbsExp_ptr<numType>(new Exp_num<numType>(x)); }


}

#endif