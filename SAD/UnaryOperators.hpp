#ifndef UnOp_H
#define UnOp_H

#include <valarray> 

#include<SAD/declarations.hpp>
#include<SAD/BinaryOperators.hpp>

namespace sad{

template<typename numType>
struct Neg:ExpressionType<numType>{
    const Expression<numType> Expr;
    Neg(const Expression<numType> &Expr):Expr( Variable<numType>(-1)*Expr ){};
    double eval() const {return Expr->eval();}
    
    Expression<numType> der(const Expression<numType> &wrt) const {return Expr->der(wrt);}

};

template<typename numType>
Expression<numType> operator-(const Expression<numType> &Expr){return Expression<numType>( new Neg<numType>(Expr) );}


template<typename numType>
Expression<numType> D(const Expression<numType> &Expr, const Expression<numType> &wrt){
    return Expr -> der(wrt) ;
}


template<typename numType>
Expression<numType> D(const Expression<numType> &Expr, const std::valarray<Expression<numType>> &wrt){
    std::valarray<Expression<numType>>  tail = wrt[ std::slice(1, wrt.size() - 1, 1) ];
    
    if(wrt.size() == 1 ){return Expr -> der(wrt[0]) ; }
    return  D(Expr -> der(wrt[0]), tail ) ;

}


}



#endif