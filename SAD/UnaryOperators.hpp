#ifndef UnOp_H
#define UnOp_H

#include <cmath> 

#include<SAD/Expression.hpp>
#include<SAD/BinaryOperators.hpp>

#define DefineUnaryOperatorClass(Operator,ClassName,evalFunc_expr,derivFunc_expr,evalFunc_num)\
template<typename numType>\
    class ClassName##_expr: public AbstractExpression<numType>{ \
        public:\
        ClassName##_expr(const Expression<numType> &expr):expr(expr){}\
        friend class Expression<numType>;\
        private:\
        Expression<numType> expr;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  derivFunc_expr;};\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc_expr;};\
    };\
template<typename numType>\
    class ClassName##_num: public AbstractExpression<numType>{ \
        public:\
        ClassName##_num(const numType &expr):expr(expr){}\
        friend class Expression<numType>;\
        private:\
        numType expr;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  ZERO<numType>;};\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc_num;};\
    };\
template<typename numType> Expression<numType> Operator(const Expression<numType> &expr){return AbsExp_ptr<numType>(new ClassName##_expr<numType>(expr)); }\
template<typename numType> Expression<numType> Operator(const numType &x){return AbsExp_ptr<numType>(new ClassName##_num<numType>(x)); }


#define toExpression(Class) Expression<numType>( AbsExp_ptr<numType>(new Class<numType>(expr) ) )


namespace sad{

template<typename numType>
    class Negation: public AbstractExpression<numType>{ \
        public:\
        Negation(const Expression<numType> &expr):expr(expr){}\
        friend class Expression<numType>;\
        private:\
        Expression<numType> expr;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  -expr.derivative(wrt);};\
        numType evaluate(const map<IDType,numType> &at)const{return -expr.evaluate(at);};\
    };

template<typename numType> Expression<numType> operator-(const Expression<numType> &expr){return AbsExp_ptr<numType>(new Negation<numType>(expr)); }\


    template<typename numType> auto n_sign(const numType &x){
        if(x>0){return static_cast<numType>(1);}
        if(x<0){return static_cast<numType>(-1);}
        return static_cast<numType>(0);
    }
    DefineUnaryOperatorClass(sign,Sign,n_sign(expr.evaluate(at)),ZERO<numType>,n_sign(expr))
    DefineUnaryOperatorClass(abs,Abs,std::abs(expr.evaluate(at)),sign(expr)*expr.derivative(wrt),std::abs(expr))

    DefineUnaryOperatorClass(sin,Sin, std::sin(expr.evaluate(at)),  expr.derivative(wrt)*cos(expr), std::sin(expr)  )
    DefineUnaryOperatorClass(cos,Cos, std::cos(expr.evaluate(at)),  - expr.derivative(wrt)*sin(expr), std::cos(expr) )

    DefineUnaryOperatorClass(log,Log,std::log(expr.evaluate(at)),  expr.derivative(wrt)/expr, std::log(expr) )

    DefineUnaryOperatorClass(exp,Exp,std::exp(expr.evaluate(at)), expr.derivative(wrt)*exp(expr), std::exp(expr))

    DefineUnaryOperatorClass(tan,Tan,std::tan(expr.evaluate(at)), (sin(expr)/cos(expr)).derivative(wrt) ,std::tan(expr))

    DefineUnaryOperatorClass(atan,ArcTan, std::atan(expr.evaluate(at)) ,( expr.derivative(wrt)/( ONE<numType> + expr * expr) ), std::atan(expr))

    DefineUnaryOperatorClass(tanh,Tanh,
    ((exp(TWO<numType>*expr)-ONE<numType>)/(exp(TWO<numType>*expr)+ONE<numType>)).evaluate(at),
    ((exp(TWO<numType>*expr)-ONE<numType>)/(exp(TWO<numType>*expr)+ONE<numType>)).derivative(wrt),
    std::tanh(expr)
    )

    DefineUnaryOperatorClass(atanh,ArcTanh,
    (HALF<numType>*( log(ONE<numType>+expr) - log(ONE<numType>-expr))).evaluate(at),
    expr.derivative(wrt)/(static_cast<numType>(1)-expr*expr),
    std::atanh(expr)
    )

    // template<typename numType> auto atanh(const Expression<numType> &x){ return   HALF<numType>*( log(ONE<numType>+x) - log(ONE<numType>-x)  ) ;}
    // template<typename numType> auto atanh(const numType &x){ return  atanh( Expression<numType>::constant(x) );}






}

#undef DefineUnaryOperatorClass
#undef DefineUnaryOperator
#undef toExpression
#endif