#ifndef UnOp_H
#define UnOp_H

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



DefineNewUnaryOperator(operator-,Neg)
DefineNewUnaryOperator(exp,Exp)
DefineNewUnaryOperator(log,Log)
DefineNewUnaryOperator(sin,Sin)
DefineNewUnaryOperator(cos,Cos)






}



#endif