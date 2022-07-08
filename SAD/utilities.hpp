#ifndef sadUtil_H
#define sadUtil_H

#include<valarray>
#include<vector>
#include<SAD/Expression.hpp>

#define msg(text) std::cout<<text
#define lb std::cout<<"\n"


namespace sad{

template<typename numType_E,typename numType_N> map<IDType,numType_E> at(const std::vector<Expression<numType_E>> &vars, const std::vector<numType_N> &values){
    map<IDType,numType_E> subs;
    if( vars.size()!=values.size() ) {  throw std::runtime_error("lists of variables has to have same size as list of values"); }

    for (IDType i = 0; i < vars.size(); i++){ subs[vars[i].ID()] = static_cast<numType_E>(values.at(i)); }
    
    return subs;
    }


// evaluate function
template<typename numType> numType evaluate(const Expression<numType> &Expr,const map<IDType,numType> &at){return Expr.evaluate(at);}


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


template<typename numType>
bool operator==(const Expression<numType> &LH, const Expression<numType> &RH){return LH.Eq(RH);}

template<typename numType>
bool is_ZERO(const Expression<numType> &expr){return expr.is_ZERO();}
template<typename numType>
bool is_ZERO(const numType &expr){return expr==static_cast<numType>(0);}

template<typename numType>
bool is_ONE(const Expression<numType> &expr){return expr.is_ONE();}
template<typename numType>
bool is_ONE(const numType &expr){return expr==static_cast<numType>(1);}


}




#endif