#ifndef BasicUnOp_H
#define BasicUnOp_H

#include <cmath> 

#include<SAD/Expression.hpp>

#define DefineUnaryOperatorClass(Operator,ClassName,evalFunc_expr,derivFunc_expr,evalFunc_num)\
template<typename numType>\
    class ClassName##_expr: public AbstractExpression<numType>{ \
        public:\
        ClassName##_expr(const Expression<numType> &expr):expr(expr){}\
        friend class Expression<numType>;\
        private:\
        Expression<numType> expr;\
        Expression<numType> derivative(const unsigned int &wrt)const{\
            if(expr.is_ZERO()){return ZERO<numType>;}\
            return  derivFunc_expr;\
        }\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc_expr;}\
    };\
template<typename numType>\
    class ClassName##_num: public AbstractExpression<numType>{ \
        public:\
        ClassName##_num(const numType &expr):expr(expr){}\
        friend class Expression<numType>;\
        private:\
        numType expr;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  ZERO<numType>;}\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc_num;}\
    };\
template<typename numType> Expression<numType> Operator(const Expression<numType> &expr){return AbsExp_ptr<numType>(new ClassName##_expr<numType>(expr)); }\
template<typename numType> Expression<numType> Operator(const numType &x){return AbsExp_ptr<numType>(new ClassName##_num<numType>(x)); }


#define toExpression(Class) Expression<numType>( AbsExp_ptr<numType>(new Class<numType>(expr) ) )


namespace sad{

template<typename numType>
    class Negation: public AbstractExpression<numType>{ 
        public:
        Negation(const Expression<numType> &expr):expr(expr){}
        friend class Expression<numType>;
        private:
        Expression<numType> expr;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto Dexpr=expr.derivative(wrt);

            if(Dexpr.is_ZERO()){return ZERO<numType>;}

            return  -expr.derivative(wrt);
        }
        numType evaluate(const map<IDType,numType> &at)const{return -expr.evaluate(at);}
    };    
template<typename numType> Expression<numType> operator-(const Expression<numType> &expr){
    if(is_ZERO(expr)){return ZERO<numType>;}
    return AbsExp_ptr<numType>(new Negation<numType>(expr)); 
}


    template<typename numType> auto n_sign(const numType &x){
        if(x==numType(0)){return static_cast<numType>(0);}
        return x/std::abs(x);
    }
    
    DefineUnaryOperatorClass(sign,Sign,
        n_sign(expr.evaluate(at)),
        ZERO<numType>,
        n_sign(expr)
    )
    
    DefineUnaryOperatorClass(abs,Abs,
        std::abs(expr.evaluate(at)),
        sign(expr)*expr.derivative(wrt),
        std::abs(expr)
    )

    DefineUnaryOperatorClass(sin,Sin,
        std::sin(expr.evaluate(at)),  
        expr.derivative(wrt)*cos(expr), 
        std::sin(expr)
    )
    
    DefineUnaryOperatorClass(cos,Cos, 
        std::cos(expr.evaluate(at)),  
        -expr.derivative(wrt)*sin(expr), 
        std::cos(expr) 
    )

    DefineUnaryOperatorClass(log,Log,
        std::log(expr.evaluate(at)),  
        expr.derivative(wrt)/expr, 
        std::log(expr) 
    )

    DefineUnaryOperatorClass(exp,Exp,
        std::exp(expr.evaluate(at)), 
        expr.derivative(wrt)*exp(expr), 
        std::exp(expr)
    )

    DefineUnaryOperatorClass(tan,Tan,
        std::tan(expr.evaluate(at)), 
        expr.derivative(wrt)/cos(expr)/cos(expr),
        std::tan(expr)
    )

    DefineUnaryOperatorClass(atan,ArcTan, 
        std::atan(expr.evaluate(at)),
        expr.derivative(wrt)/( ONE<numType> + expr * expr), 
        std::atan(expr)
    )


    DefineUnaryOperatorClass(sinh,Sinh,
        std::sinh(expr.evaluate(at)),
        expr.derivative(wrt) * cosh(expr),
        std::sinh(expr)
    )

    DefineUnaryOperatorClass(cosh,Cosh,
        std::cosh(expr.evaluate(at)),
        expr.derivative(wrt) * sinh(expr),
        std::cosh(expr)
    )


    DefineUnaryOperatorClass(tanh,Tanh,
        std::tanh(expr.evaluate(at)),
        expr.derivative(wrt)/cosh(expr)/cosh(expr),
        std::tanh(expr)
    )

    DefineUnaryOperatorClass(atanh,ArcTanh,
        std::atanh(expr.evaluate(at)),
        expr.derivative(wrt)/(static_cast<numType>(1)-expr*expr),
        std::atanh(expr)
    )

}

#undef DefineUnaryOperatorClass
#undef DefineUnaryOperator
#undef toExpression
#endif