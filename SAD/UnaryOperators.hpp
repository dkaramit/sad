#ifndef UnOp_H
#define UnOp_H

#include <cmath> 

#include<SAD/declarations.hpp>
#include<SAD/BinaryOperators.hpp>

namespace sad{




template<typename numType> struct Cos;//we need this declaration, because it is referenced in the Sin struct 
DefineUnaryOperatorClass(Sin,std::sin(Expr->eval()),(  (Expr->der(wrt))*newExpression<numType,Cos<numType>>(Expr) ))
DefineUnaryOperatorClass(Cos,std::cos(Expr->eval()),( -(Expr->der(wrt))*newExpression<numType,Sin<numType>>(Expr) ))
DefineUnaryOperatorClass(Log,std::log(Expr->eval()),(   Expr->der(wrt)/Expr ))
DefineUnaryOperatorClass(Exp,std::exp(Expr->eval()),( newExpression<numType,Exp<numType>>( Expr ) * (Expr->der(wrt)) ))
DefineUnaryOperatorClass(Neg, -1*(Expr->eval()) ,( - (Expr->der(wrt)) ))



DefineUnaryOperator(operator-,Neg)
DefineUnaryOperator(exp,Exp)
DefineUnaryOperator(log,Log)
DefineUnaryOperator(sin,Sin)
DefineUnaryOperator(cos,Cos)




}



#endif