#ifndef Declarations_H
#define Declarations_H

#include<memory>
#include<string>

namespace sad{


template<typename numType>
class ExpressionType;

template<typename numType>
using Expression = std::shared_ptr<ExpressionType<numType>>;


template<typename numType>
Expression<numType> Variable(const numType &);
template<typename numType, typename ExprType>
Expression<numType> newExpression(const Expression<numType> &);
template<typename numType, typename ExprType>
Expression<numType> newExpression(const Expression<numType> &LHS, const Expression<numType> &RHS);
}






#endif