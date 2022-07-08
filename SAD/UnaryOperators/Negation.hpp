#ifndef Neg_H
#define Neg_H

#include <cmath> 

#include<SAD/Expression.hpp>

namespace sad{

template<typename numType>
    class Negation: public AbstractExpression<numType>{ 
        public:
        Negation(const Expression<numType> &expr):expr(expr){}
        friend class Expression<numType>;
        private:
        Expression<numType> expr;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto Dexpr=expr.derivative(wrt);

            if(Dexpr.is_ZERO()){return ZERO<numType>;}

            return  -expr.derivative(wrt);
        }
        numType evaluate(const map<IDType,numType> &at)const{return -expr.evaluate(at);}
        bool is_CONST()const{return expr.is_CONST();}
        string head()const{return string("-") + str(expr);}
    };    
template<typename numType> Expression<numType> operator-(const Expression<numType> &expr){
    if(is_ZERO(expr)){return ZERO<numType>;}
    return AbsExp_ptr<numType>(new Negation<numType>(expr)); 
}

}

#endif