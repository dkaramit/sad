#ifndef BinOp_H
#define BinOp_H

#include<SAD/declarations.hpp>
#include<SAD/Expression.hpp>


namespace sad{

template<typename numType>
struct Addition:ExpressionType<numType>{
    const Expression<numType> LHS,RHS;
    Addition(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){};
    double eval() const {return LHS->eval() + RHS->eval();}
    
    Expression<numType> der(Expression<numType> &wrt) const {return LHS->der(wrt) + RHS->der(wrt) ;}

};

template<typename numType>
struct Multiplication:ExpressionType<numType>{
    const Expression<numType> LHS,RHS;
    Multiplication(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){};
    double eval() const {return LHS->eval() * RHS->eval();}
    
    Expression<numType> der(Expression<numType> &wrt) const {
        return (LHS * RHS->der(wrt)) + (RHS * LHS->der(wrt));
    }

};

template<typename numType>
Expression<numType> operator+(const Expression<numType> &LHS, const Expression<numType> &RHS){return Expression<numType>( new Addition<numType>(LHS,RHS) ); }
template<typename numType>
Expression<numType> operator*(const Expression<numType> &LHS, const Expression<numType> &RHS){return Expression<numType>( new Multiplication<numType>(LHS,RHS) ); }


}


#endif