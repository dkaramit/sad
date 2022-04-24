#ifndef BinOp_H
#define BinOp_H

#include <cmath> 
#include<SAD/Expression.hpp>

namespace sad{

/*Define addition*/
template<typename numType>
class Addition: public AbstractExpression<numType>{
    public:
    Addition(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    Expression<numType> LH,RH;
    Expression<numType> derivative(const unsigned int &id)const;
    numType evaluate()const;
};
/*this is the addition operator*/
template<typename numType>
Expression<numType> operator+(const Expression<numType> &LH, const Expression<numType> &RH){
    return AbsExp_ptr<numType>(new Addition<numType>(LH,RH));
}

/*This need to be after operator+ has been declared.*/
template<typename numType>
Expression<numType> Addition<numType>::derivative(const unsigned int &wrt)const{return LH.derivative(wrt) + RH.derivative(wrt);}
template<typename numType>
numType Addition<numType>::evaluate()const{ return LH.evaluate()+RH.evaluate(); }

/*Define multiplication*/
template<typename numType>
class Multiplication: public AbstractExpression<numType>{
    public:
    Multiplication(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    Expression<numType> LH,RH;
    Expression<numType> derivative(const unsigned int &)const;
    numType evaluate()const;
};
/*this is the multiplication operator*/
template<typename numType>
Expression<numType> operator*(const Expression<numType> &LH, const Expression<numType> &RH){
    return AbsExp_ptr<numType>(new Multiplication<numType>(LH,RH));
}

/*This need to be after operator* has been declared.*/
template<typename numType>
Expression<numType> Multiplication<numType>::derivative(const unsigned int &wrt)const{return LH.derivative(wrt)*RH+LH*RH.derivative(wrt);}
template<typename numType>
numType Multiplication<numType>::evaluate()const{ return LH.evaluate()*RH.evaluate(); }





}


#endif