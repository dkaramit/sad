#ifndef UnOp_H
#define UnOp_H

#include <cmath> 

#include<SAD/declarations.hpp>
#include<SAD/BinaryOperators.hpp>

namespace sad{

template<typename numType> struct Cos;//we need this declaration, because Cos referenced in the Sin struct 
DefineUnaryOperatorClass(sin,Sin,std::sin(Expr->eval()),(  (Expr->der(wrt))*newExpression<numType,Cos<numType>>(Expr) ))
DefineUnaryOperatorClass(cos,Cos,std::cos(Expr->eval()),( -(Expr->der(wrt))*newExpression<numType,Sin<numType>>(Expr) ))
DefineUnaryOperatorClass(log,Log,std::log(Expr->eval()),(   Expr->der(wrt)/Expr ))
DefineUnaryOperatorClass(exp,Exp,std::exp(Expr->eval()),( newExpression<numType,Exp<numType>>( Expr ) * (Expr->der(wrt)) ))
DefineUnaryOperatorClass(operator-,Neg, -Expr->eval() ,( - (Expr->der(wrt)) ))



}



#endif