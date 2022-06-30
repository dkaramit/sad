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
template<typename numType> Expression<numType> OP(const Expression<numType> &expr){return AbsExp_ptr<numType>(new CLASS<numType>(expr)); }\
template<typename numType> Expression<numType> OP(const numType &x){return OP(Expression<numType>::constant(x)); }


#define toExpression(Class) Expression<numType>( AbsExp_ptr<numType>(new Class<numType>(expr) ) )


namespace sad{

    template<typename numType> class Sin;
    template<typename numType> class Cos;

    DefineUnaryOperatorClass(operator-,Neg, - expr.evaluate(at), - expr.derivative(wrt) )

    template<typename numType> auto n_sign(const numType &x){
        if(x>0){return static_cast<numType>(1);}
        if(x<0){return static_cast<numType>(-1);}
        return static_cast<numType>(0);
    }
    DefineUnaryOperatorClass(sign,Sign,n_sign(expr.evaluate(at)),ZERO<numType>)
    DefineUnaryOperatorClass(abs,Abs,std::abs(expr.evaluate(at)),sign(expr)*expr.derivative(wrt))

    DefineUnaryOperatorClass(sin,Sin, std::sin(expr.evaluate(at)),  expr.derivative(wrt)*cos(expr)  )
    DefineUnaryOperatorClass(cos,Cos, std::cos(expr.evaluate(at)),  - expr.derivative(wrt)*sin(expr) )

    DefineUnaryOperatorClass(log,Log,std::log(expr.evaluate(at)),(  expr.derivative(wrt)/expr ))

    DefineUnaryOperatorClass(exp,Exp,std::exp(expr.evaluate(at)), expr.derivative(wrt)*exp(expr))


    template<typename numType> auto tan(const Expression<numType> &expr){return sin(expr)/cos(expr);}
    template<typename numType> auto tan(const numType &x){return  tan( Expression<numType>::constant(x) );}

    DefineUnaryOperatorClass(atan,ArcTan, std::atan(expr.evaluate(at)) ,( expr.derivative(wrt)/( ONE<numType> + expr * expr) ))

    template<typename numType>
    auto tanh(const Expression<numType> &x){ return (exp(TWO<numType>*x)-ONE<numType>)/(exp(TWO<numType>*x)+ONE<numType>);}
    template<typename numType> auto tanh(const numType &x){ return   tanh( Expression<numType>::constant(x) );}

    template<typename numType> auto atanh(const Expression<numType> &x){ return   HALF<numType>*( log(ONE<numType>+x) - log(ONE<numType>-x)  ) ;}
    template<typename numType> auto atanh(const numType &x){ return  atanh( Expression<numType>::constant(x) );}






}

#undef DefineUnaryOperatorClass
#undef DefineUnaryOperator
#undef toExpression
#endif