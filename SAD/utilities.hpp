#ifndef sadUtil_H
#define sadUtil_H

#include<valarray>
#include<SAD/Expression.hpp>


namespace sad{
// evaluate function
template<typename numType> numType evaluate(const Expression<numType> &Expr){return Expr.evaluate();}


/*You can use these functions to take the derivative easier*/

//derivative with respect to a variable (it takes the id of the variable as unsigned it)
template<typename numType>Expression<numType> derivative(const Expression<numType> &Expr, const unsigned int &wrt){return Expr.derivative(wrt);}

//derivative with respect to a valarray of ids
template<typename numType> Expression<numType> derivative(const Expression<numType> &Expr, const std::valarray<unsigned int> &wrt){
    std::valarray<unsigned int>  tail= wrt[ std::slice(1, wrt.size() - 1, 1) ];
    if(wrt.size() == 1 ){return Expr.derivative(wrt[0]) ; }
    return  derivative( Expr.derivative(wrt[0]) , tail ) ;
}

//this does the same as derivative(const Expression<numType> &Expr, const std::valarray<unsigned int> &wrt), but you can call it
// using a parameter pack of instances of Expression
template<typename numType,typename... Args>
Expression<numType> derivative(const Expression<numType> &Expr, const Args&... vars){ return  derivative(Expr, std::valarray<unsigned int>{vars.ID()...}) ;}



}




#endif