#ifndef Declarations_H
#define Declarations_H
#include <valarray> 

/*These macros make the definition of new operators easier*/
#define DefineNewBinaryOperator(op,expr) template<typename numType> Expression<numType> op(const Expression<numType> &LHS, const Expression<numType> &RHS){return newExpression<numType,expr<numType>>(LHS,RHS); }
#define DefineNewUnaryOperator(op,expr)template<typename numType> Expression<numType> op(const Expression<numType> &Expr){return newExpression<numType,expr<numType>>( Expr );}

namespace sad{


template<typename numType>
class ExpressionType;
template<typename numType>
class VariableType;

template<typename numType>
using Expression = std::shared_ptr<ExpressionType<numType>>;


template<typename numType>
Expression<numType> Variable(const numType &);
template<typename numType, typename ExprType>
Expression<numType> newExpression(const Expression<numType> &);
template<typename numType, typename ExprType>
Expression<numType> newExpression(const Expression<numType> &LHS, const Expression<numType> &RHS);


/*functions that can be used to declare variables and expressions easier (it is better to hide the fact tha everything is a pointer, behind these functions)*/
template<typename numType>
Expression<numType> Variable(const numType &x){return Expression<numType>(new VariableType<numType>(x));}
template<typename numType, typename ExprType>
Expression<numType> newExpression(const Expression<numType> &Expr){ return Expression<numType>( new ExprType(Expr) );}
template<typename numType, typename ExprType>
Expression<numType> newExpression(const Expression<numType> &LHS, const Expression<numType> &RHS){ return Expression<numType>( new ExprType(LHS,RHS) );}


/*functions to get the derivates and evaluate the expressions*/
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