#ifndef UnOp_H
#define UnOp_H

#include <cmath> 

#include<SAD/declarations.hpp>
#include<SAD/BinaryOperators.hpp>

namespace sad{


template<typename numType>
    struct Neg:ExpressionType<numType>{ 
        const Expression<numType> Expr; 
        Neg(const Expression<numType> &Expr):Expr(Expr){}; 
        numType eval() const {return -Expr->eval();} 
        Expression<numType> der(const Expression<numType> &wrt) const {return  - (Expr->der(wrt)) ;} 
};
template<typename numType> Expression<numType> operator-(const Expression<numType> &Expr){return newExpression<numType,Neg<numType>>( Expr );}\



template<typename numType> struct Cos;//we need this declaration, because Cos referenced in the Sin struct 
DefineUnaryOperatorClass(sin,Sin,std::sin(Expr->eval()),(  (Expr->der(wrt))*newExpression<numType,Cos<numType>>(Expr) ))

DefineUnaryOperatorClass(cos,Cos,std::cos(Expr->eval()),( -(Expr->der(wrt))*newExpression<numType,Sin<numType>>(Expr) ))

DefineUnaryOperatorClass(log,Log,std::log(Expr->eval()),(   Expr->der(wrt)/Expr ))

DefineUnaryOperatorClass(exp,Exp,std::exp(Expr->eval()),( newExpression<numType,Exp<numType>>( Expr ) * (Expr->der(wrt)) ))

// DefineUnaryOperatorClass(sqrt,Sqrt,std::sqrt(Expr->eval()),( newExpression<numType,Sqrt<numType>>( Expr ) * (Expr->der(wrt)) ))

DefineUnaryOperatorClass(erf,Erf,std::erf(Expr->eval()),(
    Two<numType>/SqrtPi<numType>*newExpression<numType,Exp<numType>>(- Expr*Expr ) * Expr->der(wrt)
))
template<typename numType> 
auto erfc(const Expression<numType> &x){return One<numType>-erf(x);}


template<typename numType>
auto tan(const Expression<numType> &x){return sin(x)/cos(x);}
template<typename numType>
auto tan(const numType &x){return Variable<numType>(std::tan(x));}
DefineUnaryOperatorClass(atan,ArcTan, std::atan(Expr->eval()) ,(  Expr->der(wrt)/( One<numType> + Expr * Expr) ))

template<typename numType>
auto tanh(const Expression<numType> &x){ return   (exp(Two<numType>*x)-One<numType>)/(exp(Two<numType>*x)+One<numType>);}

template<typename numType>
auto atanh(const Expression<numType> &x){ return   Half<numType>*( log(One<numType>+x) - log(One<numType>-x)  ) ;}

template<typename argType,typename numType>
struct BesselK:ExpressionType<numType>{
    const argType i;
    const Expression<numType> Expr;
    BesselK(const argType &i, const Expression<numType> &Expr):i( std::abs(i) ),Expr(Expr){};

    numType eval() const {return  std::cyl_bessel_k(i,Expr->eval())  ;}
    
    Expression<numType> der(const Expression<numType> &wrt) const {
        return  -Half<numType>*(newExpression<numType,BesselK<argType,numType>>(i+1,Expr) + newExpression<numType,BesselK<argType,numType>>(i-1,Expr))*Expr->der(wrt) ;
    }
};
template<typename argType,typename numType>
auto cyl_bessel_k(const argType &i, const Expression<numType> &Expr){return newExpression<numType,BesselK<argType,numType>>(i,Expr); }
template<typename argType,typename numType>
auto cyl_bessel_k(const argType &i, const numType &Expr){return Variable<numType>(std::cyl_bessel_k(i,Expr)) ; }


}



#endif