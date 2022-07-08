#ifndef Mult_H
#define Mult_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/BinaryOperators/Addition.hpp>
#include<SAD/utilities.hpp>


#define Simplifications if(is_ZERO(LH) or is_ZERO(RH)){return ZERO<numType>;} if(is_ONE(LH)){return RH;} if(is_ONE(RH)){return LH;}


namespace sad{

template<typename numType>
    class Multiplication_expr: public AbstractExpression<numType>{ 
        public:
        Multiplication_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH,RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            if(RH==LH){return TWO<numType>*LH*LH.derivative(wrt);}

            return  LH.derivative(wrt)*RH + LH*RH.derivative(wrt);
        }
        numType evaluate(const map<IDType,numType> &at)const{return LH.evaluate(at)*RH.evaluate(at);}
        bool is_CONST()const{return LH.is_CONST() and RH.is_CONST();}
        string head()const{return str(LH) + string("*") + str(RH);}
    };
template<typename numType>
    class Multiplication_numL: public AbstractExpression<numType>{ 
        public:
        Multiplication_numL(const numType &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        numType LH;
        Expression<numType> RH;
        Expression<numType> derivative(const unsigned int &wrt)const{ return  LH*RH.derivative(wrt);}
        numType evaluate(const map<IDType,numType> &at)const{return LH*RH.evaluate(at);}
        bool is_CONST()const{return RH.is_CONST();}
        string head()const{return str(LH) + string("*") + str(RH);}
    };

template<typename numType> Expression<numType> operator*(const Expression<numType> &LH, const Expression<numType> &RH){
    if(RH.is_CONST()){return AbsExp_ptr<numType>(new Multiplication_expr<numType>(RH,LH));}
    Simplifications
    return AbsExp_ptr<numType>(new Multiplication_expr<numType>(LH,RH)); 
}

template<typename numType> Expression<numType> operator*(const numType &LH, const Expression<numType> &RH){
    Simplifications
    return AbsExp_ptr<numType>(new Multiplication_numL<numType>(LH,RH)); 
}

template<typename numType> Expression<numType> operator*(const Expression<numType> &LH, const numType &RH){
    Simplifications
    return AbsExp_ptr<numType>(new Multiplication_numL<numType>(RH,LH)); 
}

}

#undef Simplifications
#endif