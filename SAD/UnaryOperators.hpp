#ifndef UnOp_H
#define UnOp_H

#include <valarray> 
#include <cmath> 

#include<SAD/declarations.hpp>
#include<SAD/BinaryOperators.hpp>

namespace sad{

template<typename numType>
struct Neg:ExpressionType<numType>{
    const Expression<numType> Expr;
    Neg(const Expression<numType> &Expr):Expr( Expr ){};
    numType eval() const {return -Expr->eval();}
    
    Expression<numType> der(const Expression<numType> &wrt) const {return Variable<numType>(-1)*Expr->der(wrt);}

};

template<typename numType>
struct Exp:ExpressionType<numType>{
    const Expression<numType> Expr;
    Exp(const Expression<numType> &Expr):Expr(Expr){};
    numType eval() const {return std::exp(Expr->eval());}
    
    Expression<numType> der(const Expression<numType> &wrt) const {return newExpression<numType,Exp<numType>>( Expr ) * (Expr->der(wrt));}

};

template<typename numType>
struct Log:ExpressionType<numType>{
    const Expression<numType> Expr;
    Log(const Expression<numType> &Expr):Expr(Expr){};
    numType eval() const {return std::log(Expr->eval());}
    
    Expression<numType> der(const Expression<numType> &wrt) const {return  (Expr->der(wrt))/Expr ;}

};

template<typename numType>
struct Cos;

template<typename numType>
struct Sin:ExpressionType<numType>{
    const Expression<numType> Expr;
    Sin(const Expression<numType> &Expr):Expr(Expr){};
    numType eval() const {return std::sin(Expr->eval());}
    
    Expression<numType> der(const Expression<numType> &wrt) const {return  (Expr->der(wrt)) * newExpression<numType,Cos<numType>>( Expr );}

};

template<typename numType>
struct Cos:ExpressionType<numType>{
    const Expression<numType> Expr;
    Cos(const Expression<numType> &Expr):Expr(Expr){};
    numType eval() const {return std::cos(Expr->eval());}
    
    Expression<numType> der(const Expression<numType> &wrt) const {return  -(Expr->der(wrt))* newExpression<numType,Sin<numType>>( Expr );}

};



template<typename numType>
Expression<numType> operator-(const Expression<numType> &Expr){return newExpression<numType,Neg<numType>>( Expr );}

template<typename numType>
Expression<numType> exp(const Expression<numType> &Expr){return newExpression<numType,Exp<numType>>( Expr );}

template<typename numType>
Expression<numType> log(const Expression<numType> &Expr){return newExpression<numType,Log<numType>>( Expr );}

template<typename numType>
Expression<numType> sin(const Expression<numType> &Expr){return newExpression<numType,Sin<numType>>( Expr );}

template<typename numType>
Expression<numType> cos(const Expression<numType> &Expr){return newExpression<numType,Cos<numType>>( Expr );}






















template<typename numType>
Expression<numType> derivative(const Expression<numType> &Expr, const Expression<numType> &wrt){return Expr -> der(wrt);}

template<typename numType>
Expression<numType> derivative(const Expression<numType> &Expr, const std::valarray<Expression<numType>> &wrt){
    std::valarray<Expression<numType>>  tail = wrt[ std::slice(1, wrt.size() - 1, 1) ];
    if(wrt.size() == 1 ){return Expr -> der(wrt[0]) ; }
    return  derivative(Expr -> der(wrt[0]), tail ) ;
}

template<typename numType>
auto evaluate(const Expression<numType> &Expr){return Expr->eval();}


}



#endif