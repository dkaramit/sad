#ifndef Add_H
#define Add_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/BinaryOperators/Multiplication.hpp>
#include<SAD/utilities.hpp>


namespace sad{

template<typename numType>
    class Addition_expr: public AbstractExpression<numType>{ 
        public:
        Addition_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        Expression<numType> LH,RH;
        Expression<numType> derivative(const unsigned int &wrt)const{
            auto DLH=LH.derivative(wrt);
            auto DRH=RH.derivative(wrt);
            
            if(DLH.is_ZERO() and DRH.is_ZERO()){return ZERO<numType>;}
            if(RH.Eq(LH)){return TWO<numType>*DLH;}


            if(DLH.is_ZERO()){return DRH;}
            if(DRH.is_ZERO()){return DLH;}

            return  DLH + DRH;
        }
        numType evaluate(const map<IDType,numType> &at)const{return LH.evaluate(at)+RH.evaluate(at);}
    };
template<typename numType>
    class Addition_numL: public AbstractExpression<numType>{ 
        public:
        Addition_numL(const numType &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
        friend class Expression<numType>;
        private:
        numType LH;
        Expression<numType> RH;
        Expression<numType> derivative(const unsigned int &wrt)const{return  RH.derivative(wrt);}
        numType evaluate(const map<IDType,numType> &at)const{return LH+RH.evaluate(at);}
    };


template<typename numType> Expression<numType> operator+(const Expression<numType> &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new Addition_expr<numType>(LH,RH)); }

template<typename numType> Expression<numType> operator+(const numType &LH, const Expression<numType> &RH){return AbsExp_ptr<numType>(new Addition_numL<numType>(LH,RH)); }

template<typename numType> Expression<numType> operator+(const Expression<numType> &LH, const numType &RH){return AbsExp_ptr<numType>(new Addition_numL<numType>(RH,LH)); }

}


#endif