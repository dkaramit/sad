#ifndef Mult_H
#define Mult_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/BinaryOperators/Addition.hpp>
#include<SAD/utilities.hpp>


namespace sad{

template<typename numType>
    class Multiplication_expr: public AbstractExpression<numType>{ 
        public:
        Multiplication_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH,RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DLH=LH.derivative(wrt);
            auto DRH=RH.derivative(wrt);
            
            if(DLH.is_ZERO() and DRH.is_ZERO()){return ZERO<numType>;}
            if(DLH.is_ONE() and DRH.is_ONE()){return LH + RH;}

            if(RH.Eq(LH)){return TWO<numType>*LH*DLH;}

            if(DLH.is_ZERO()){return LH*DRH;}
            if(DRH.is_ZERO()){return DLH*RH;}

            if(DLH.is_ONE()){return RH + LH*DRH;}
            if(DRH.is_ONE()){return DLH*RH + LH;}


            return  DLH*RH + LH*DRH;
        }
        numType evaluate(const map<IDType,numType> &at)const{return LH.evaluate(at)*RH.evaluate(at);}
    };
template<typename numType>
    class Multiplication_numL: public AbstractExpression<numType>{ 
        public:
        Multiplication_numL(const numType &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        numType LH;
        Expression<numType> RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DRH=RH.derivative(wrt);

            if(LH == static_cast<numType>(0)){return ZERO<numType>;}
            if(DRH.is_ZERO()){return ZERO<numType>;}
            if(LH == static_cast<numType>(1)){return DRH;}

            return  LH*DRH;
        }
        numType evaluate(const map<IDType,numType> &at)const{return LH*RH.evaluate(at);}
    };

template<typename numType> Expression<numType> operator*(const Expression<numType> &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new Multiplication_expr<numType>(LH,RH)); }

template<typename numType> Expression<numType> operator*(const numType &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new Multiplication_numL<numType>(LH,RH)); }

template<typename numType> Expression<numType> operator*(const Expression<numType> &LH, const numType &RH){return AbsExp_ptr<numType>(new Multiplication_numL<numType>(RH,LH)); }

}


#endif