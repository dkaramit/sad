#ifndef BinOp_H
#define BinOp_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/utilities.hpp>


#define DefineBinaryOperatorClass(Operator,ClassName,evalFunc_expr,derivFunc_expr,evalFunc_numL,derivFunc_numL,evalFunc_numR,derivFunc_numR)\
template<typename numType>\
    class ClassName##_expr: public AbstractExpression<numType>{ \
        public:\
        ClassName##_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}\
        friend class Expression<numType>;\
        private:\
        Expression<numType> LH,RH;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  derivFunc_expr;};\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc_expr;};\
    };\
template<typename numType>\
    class ClassName##_numL: public AbstractExpression<numType>{ \
        public:\
        ClassName##_numL(const numType &LH, const Expression<numType> &RH):LH(LH),RH(RH){}\
        friend class Expression<numType>;\
        private:\
        numType LH;\
        Expression<numType> RH;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  derivFunc_numL;};\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc_numL;};\
    };\
template<typename numType>\
    class ClassName##_numR: public AbstractExpression<numType>{ \
        public:\
        ClassName##_numR(const Expression<numType> &LH, const numType &RH):LH(LH),RH(RH){}\
        friend class Expression<numType>;\
        private:\
        Expression<numType> LH;\
        numType RH;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  derivFunc_numR;};\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc_numR;};\
    };\
    DefineBinaryOperator_expr(Operator,ClassName)\
    DefineBinaryOperator_numL(Operator,ClassName)\
    DefineBinaryOperator_numR(Operator,ClassName)


#define DefineBinaryOperator_expr(OP,CLASS) \
template<typename numType> Expression<numType> OP(const Expression<numType> &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new CLASS##_expr<numType>(LH,RH)); }\

#define DefineBinaryOperator_numL(OP,CLASS) \
template<typename numType> Expression<numType> OP(const numType &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new CLASS##_numL<numType>(LH,RH)); }\

#define DefineBinaryOperator_numR(OP,CLASS) \
template<typename numType> Expression<numType> OP(const Expression<numType> &LH, const numType &RH){return AbsExp_ptr<numType>(new CLASS##_numR<numType>(LH,RH)); }\


namespace sad{

    DefineBinaryOperatorClass(operator+,Addition, LH.evaluate(at)+RH.evaluate(at) , LH.derivative(wrt) + RH.derivative(wrt)
                                                , LH             +RH.evaluate(at) ,                      RH.derivative(wrt)
                                                , LH.evaluate(at)+RH              , LH.derivative(wrt)
                                                )

    DefineBinaryOperatorClass(operator-,Subtruction, LH.evaluate(at)-RH.evaluate(at) , LH.derivative(wrt) - RH.derivative(wrt)
                                                , LH             -RH.evaluate(at) ,                       - RH.derivative(wrt)
                                                , LH.evaluate(at)-RH              , LH.derivative(wrt)
                                                )

    DefineBinaryOperatorClass(operator*,Multiplication, LH.evaluate(at)*RH.evaluate(at) , LH.derivative(wrt)*RH + LH*RH.derivative(wrt)
                                                , LH             *RH.evaluate(at) ,                      LH*RH.derivative(wrt)
                                                , LH.evaluate(at)*RH              , LH.derivative(wrt)*RH
                                                )
    
    DefineBinaryOperatorClass(operator/,Division, LH.evaluate(at)/RH.evaluate(at) , LH.derivative(wrt)/RH - LH*RH.derivative(wrt)/RH/RH
                                                , LH             /RH.evaluate(at) ,                       - LH*RH.derivative(wrt)/RH/RH
                                                , LH.evaluate(at)/RH              , LH.derivative(wrt)/RH 
                                                )
}


#undef DefineBinaryOperatorClass
#undef DefineBinaryOperator

#endif