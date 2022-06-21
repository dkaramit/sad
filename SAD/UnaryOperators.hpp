#ifndef UnOp_H
#define UnOp_H

#include <cmath> 

#include<SAD/Expression.hpp>
#include<SAD/BinaryOperators.hpp>

#define DefineUnaryOperatorClass(Operator,ClassName,evalFunc,derivFunc)template<typename numType>\
    class ClassName: public AbstractExpression<numType>{ \
        public:\
        ClassName(const Expression<numType> &expr):expr(expr){}\
        friend class Expression<numType>;\
        private:\
        Expression<numType> expr;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  derivFunc;};\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc;};\
    };\
DefineUnaryOperator(Operator,ClassName)

#define DefineUnaryOperator(OP,CLASS) \
template<typename numType> Expression<numType> OP(const Expression<numType> &expr){return AbsExp_ptr<numType>(new CLASS<numType>(expr)); }


#define toExpression(Class) Expression<numType>( AbsExp_ptr<numType>(new Class<numType>(expr) ) )


namespace sad{

    template<typename numType> class Sin;
    template<typename numType> class Cos;

    DefineUnaryOperatorClass(operator-,Neg, - expr.evaluate(at), - expr.derivative(wrt) )
    DefineUnaryOperatorClass(sin,Sin, std::sin(expr.evaluate(at)),  expr.derivative(wrt)*toExpression(Cos)  )
    DefineUnaryOperatorClass(cos,Cos, std::cos(expr.evaluate(at)),  - expr.derivative(wrt)*toExpression(Sin) )

}



#endif