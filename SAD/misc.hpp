#ifndef MISC_H
#define MISC_H

#include <iostream>
#include<memory>
#include<map>
#include<vector>
#include<string>

#define PPF std::cout<<__PRETTY_FUNCTION__<<"\n"

namespace sad{
using std::map;
using std::vector;
using std::string;
using std::to_string;
using std::shared_ptr;
using std::make_shared;

using IDType=unsigned int;


/*declaration of classes*/
template<typename numType> class AbstractExpression;
template<typename numType> class Variable;
template<typename numType> class Expression;

/*Alias for shared pointer to AbstractExpression*/
template<typename numType> using AbsExp_ptr=shared_ptr<AbstractExpression<numType>>; 



/*----these constants will be helpful---*/
template<typename numType>static const auto ONE     = Expression<numType>::constant(1);
template<typename numType>static const auto TWO     = Expression<numType>::constant(2);
template<typename numType>static const auto ZERO    = Expression<numType>::constant(0);
template<typename numType>static const auto NEG_ONE = Expression<numType>::constant(-1);
template<typename numType>static const auto HALF    = Expression<numType>::constant(0.5);
template<typename numType>static const auto PI      = Expression<numType>::constant(M_PI);
template<typename numType>static const auto PI2     = Expression<numType>::constant(M_PI*M_PI);
template<typename numType>static const auto SQRT_PI = Expression<numType>::constant(2/M_2_SQRTPI);

//you can use this to evaluate constants!
template<typename numType>static const map<IDType,numType> empty_at;

template<typename numType> auto print_expr(const Expression<numType> &expr){return expr.str();}
template<typename numType> auto print_expr(const numType &x){return to_string(x);}

}



#endif