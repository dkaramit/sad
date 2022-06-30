#ifndef BinOp_H
#define BinOp_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/utilities.hpp>

// #define sadCT(l,r) typename std::common_type<l,r>::type; 



#define DefineBinaryOperatorClass(Operator,ClassName,evalFunc,derivFunc)template<typename numType>\
    class ClassName: public AbstractExpression<numType>{ \
        public:\
        ClassName(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}\
        friend class Expression<numType>;\
        private:\
        Expression<numType> LH,RH;\
        Expression<numType> derivative(const unsigned int &wrt)const{return  derivFunc;};\
        numType evaluate(const map<IDType,numType> &at)const{return evalFunc;};\
    };\
DefineBinaryOperator(Operator,ClassName)

#define DefineBinaryOperator(OP,CLASS) \
template<typename numType> Expression<numType> OP(const Expression<numType> &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new CLASS<numType>(LH,RH)); }\
template<typename numType, typename LD> Expression<numType> OP(const LD &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new CLASS<numType>(Expression<numType>::constant(LH),RH)); }\
template<typename numType, typename LD> Expression<numType> OP(const Expression<numType> &LH, const LD &RH){return AbsExp_ptr<numType>(new CLASS<numType>(LH,Expression<numType>::constant(RH))); }


namespace sad{

    DefineBinaryOperatorClass(operator+,Addition, LH.evaluate(at)+RH.evaluate(at) , LH.derivative(wrt) + RH.derivative(wrt))
    DefineBinaryOperatorClass(operator-,Subtruction, LH.evaluate(at)-RH.evaluate(at) , LH.derivative(wrt) - RH.derivative(wrt))
    DefineBinaryOperatorClass(operator*,Multiplication, LH.evaluate(at)*RH.evaluate(at) , LH.derivative(wrt)*RH+LH*RH.derivative(wrt))
    DefineBinaryOperatorClass(operator/,Division, LH.evaluate(at)/RH.evaluate(at) , LH.derivative(wrt)/RH - LH*RH.derivative(wrt)/RH/RH)

}


#undef DefineBinaryOperatorClass
#undef DefineBinaryOperator

#endif