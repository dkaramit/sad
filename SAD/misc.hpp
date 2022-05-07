#ifndef MISC_H
#define MISC_H

#include <iostream>
#include<memory>

#define PPF std::cout<<__PRETTY_FUNCTION__<<"\n"

namespace sad{
/*declaration of classes*/
template<typename numType> class AbstractExpression;
template<typename numType> class Variable;
template<typename numType> class Expression;

/*Alias for shared pointer to AbstractExpression*/
template<typename numType> using AbsExp_ptr=std::shared_ptr<AbstractExpression<numType>>; 



/*----these constants will be helpful---*/
template<typename numType>static const auto ONE     = Expression<numType>::constant(1);
template<typename numType>static const auto ZERO    = Expression<numType>::constant(0);
template<typename numType>static const auto NEG_ONE = Expression<numType>::constant(-1);
template<typename numType>static const auto HALF    = Expression<numType>::constant(0.5);
template<typename numType>static const auto PI      = Expression<numType>::constant(M_PI);
template<typename numType>static const auto PI2     = Expression<numType>::constant(M_PI*M_PI);
template<typename numType>static const auto SQRT_PI = Expression<numType>::constant(2/M_2_SQRTPI);


}



#endif