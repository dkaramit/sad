#ifndef LogOp_H
#define LogOp_H

#include <cmath> 

#include<SAD/Expression.hpp>
#include<SAD/UnaryOperators/Negation.hpp>



namespace sad{

template<typename numType>
class Log_expr: public AbstractExpression<numType>{ 
    public:
    Log_expr(const Expression<numType> &expr):expr(expr){}
    friend class Expression<numType>;
    private:
    Expression<numType> expr;
    Expression<numType> derivative(const unsigned int &wrt)const{
        if(expr.is_ZERO()){return ZERO<numType>;}
        return  expr.derivative(wrt)/expr;
    }
    numType evaluate(const map<IDType,numType> &at)const{return std::log(expr.evaluate(at));}
    bool is_CONST()const{return expr.is_CONST();}
    string str()const{return string("log") + string("(") + print_expr(expr) + string(")");}
    string head()const{return string("log");}
    Expression<numType> subExpr()const{return expr;}
};
template<typename numType>
class Log_num: public AbstractExpression<numType>{ 
    public:
    Log_num(const numType &expr):expr(expr){}
    friend class Expression<numType>;
    private:
    numType expr;
    Expression<numType> derivative(const unsigned int &wrt)const{return  ZERO<numType>;}
    numType evaluate(const map<IDType,numType> &at)const{return std::log(expr);}
    bool is_CONST()const{return true;}
    string str()const{return string("log") + string("(") + print_expr(expr) + string(")");}
    string head()const{return string("log");}
    Expression<numType> subExpr()const{return expr;}
    };
template<typename numType> Expression<numType> log(const Expression<numType> &expr){
    if(expr.head() == "exp"){return expr.subExpr();}
    return AbsExp_ptr<numType>(new Log_expr<numType>(expr)); 
}
template<typename numType> Expression<numType> log(const numType &x){return AbsExp_ptr<numType>(new Log_num<numType>(x)); }


}

#endif