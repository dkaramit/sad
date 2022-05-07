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
template<typename numType>static const auto ONE     = Expression<numType>::variable(1);
template<typename numType>static const auto ZERO    = Expression<numType>::variable(0);
template<typename numType>static const auto NEG_ONE = Expression<numType>::variable(-1);
template<typename numType>static const auto HALF    = Expression<numType>::variable(0.5);
template<typename numType>static const auto PI      = Expression<numType>::variable(M_PI);
template<typename numType>static const auto PI2     = Expression<numType>::variable(M_PI*M_PI);
template<typename numType>static const auto SQRT_PI = Expression<numType>::variable(2/M_2_SQRTPI);


}



#endif