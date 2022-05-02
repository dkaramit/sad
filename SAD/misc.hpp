#ifndef Declarations_H
#define Declarations_H

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
template<typename numType>static const Expression<numType> ONE(1,false);
template<typename numType>static const Expression<numType> ZERO(0,false);
template<typename numType>static const Expression<numType> NEG_ONE(-1,false);
template<typename numType>static const Expression<numType> HALF(0.5,false);
template<typename numType>static const Expression<numType> PI(M_PI,false);
template<typename numType>static const Expression<numType> PI2(M_PI*M_PI,false);
template<typename numType>static const Expression<numType> SQRT_PI(2/M_2_SQRTPI,false);


}



#endif