#ifndef Sub_H
#define Sub_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/utilities.hpp>

#include<SAD/BinaryOperators/Multiplication.hpp>

namespace sad{

template<typename numType>
    class Subtruction_expr: public AbstractExpression<numType>{ 
        public:
        Subtruction_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH,RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DLH=LH.derivative(wrt);
            auto DRH=RH.derivative(wrt);
            
            if(DLH.is_ZERO() and DRH.is_ZERO()){return ZERO<numType>;}
            
            if(DLH.is_ZERO()){return static_cast<numType>(-1)*DRH;}
            if(DRH.is_ZERO()){return DLH;}

            return DLH - DRH;
        }
        numType evaluate(const map<IDType,numType> &at)const{return  LH.evaluate(at)-RH.evaluate(at);}
    };
template<typename numType>
    class Subtruction_numL: public AbstractExpression<numType>{ 
        public:
        Subtruction_numL(const numType &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        numType LH;
        Expression<numType> RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DRH=RH.derivative(wrt);

            if(DRH.is_ZERO()){return ZERO<numType>;}

            return  -DRH;
        }
        numType evaluate(const map<IDType,numType> &at)const{return LH-RH.evaluate(at);}
    };
template<typename numType>
    class Subtruction_numR: public AbstractExpression<numType>{ 
        public:
        Subtruction_numR(const Expression<numType> &LH, const numType &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH;
        numType RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DLH=LH.derivative(wrt);
            return  DLH;
        }
        numType evaluate(const map<IDType,numType> &at)const{return LH.evaluate(at)-RH;}
    };


template<typename numType> Expression<numType> operator-(const Expression<numType> &LH, const Expression<numType> &RH){
    if(RH.Eq(LH)){return ZERO<numType>;}
    if(LH.is_ZERO()){return -RH;}
    if(RH.is_ZERO()){return LH;}

    return AbsExp_ptr<numType>(new Subtruction_expr<numType>(LH,RH)); 
}

template<typename numType> Expression<numType> operator-(const numType &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new Subtruction_numL<numType>(LH,RH)); }

template<typename numType> Expression<numType> operator-(const Expression<numType> &LH, const numType &RH){return AbsExp_ptr<numType>(new Subtruction_numR<numType>(LH,RH)); }

}


#endif