#ifndef Div_H
#define Div_H

#include <cmath> 
#include<SAD/Expression.hpp>
#include<SAD/utilities.hpp>

#include<SAD/BinaryOperators/Multiplication.hpp>

#define Simplifications if(is_ONE(RH)){return LH;}

namespace sad{

template<typename numType>
class Division_expr: public AbstractExpression<numType>{ 
    public:
    Division_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    Expression<numType> LH,RH;
    Expression<numType> derivative(const unsigned int &wrt)const{ return LH.derivative(wrt)/RH - LH/(RH*RH)*RH.derivative(wrt); }
    numType evaluate(const map<IDType,numType> &at)const{return  LH.evaluate(at)/RH.evaluate(at);}
    bool is_CONST()const{return LH.is_CONST() and RH.is_CONST();}
    string str()const{return print_expr(LH) + string("/") + print_expr(RH);}
    string head()const{return str();}
    Expression<numType> subExpr(){return  LH/RH;}
};
template<typename numType>
class Division_numL: public AbstractExpression<numType>{ 
    public:
    Division_numL(const numType &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    numType LH;
    Expression<numType> RH;
    Expression<numType> derivative(const unsigned int &wrt)const{ return  -LH/(RH*RH)*RH.derivative(wrt); }
    numType evaluate(const map<IDType,numType> &at)const{return LH/RH.evaluate(at);}
    bool is_CONST()const{return RH.is_CONST();}
    string str()const{return print_expr(LH) + string("/") + print_expr(RH);}
    string head()const{return str();}
    Expression<numType> subExpr(){return  LH/RH;}
};
template<typename numType>
class Division_numR: public AbstractExpression<numType>{ 
    public:
    Division_numR(const Expression<numType> &LH, const numType &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    Expression<numType> LH;
    numType RH;
    Expression<numType> derivative(const unsigned int &wrt)const{ return  LH.derivative(wrt)/RH; }
    numType evaluate(const map<IDType,numType> &at)const{return LH.evaluate(at)/RH;}
    bool is_CONST()const{return LH.is_CONST();}
    string str()const{return print_expr(LH) + string("/") + print_expr(RH);}
    string head()const{return str();}
    Expression<numType> subExpr(){return  LH/RH;}
};


template<typename numType> Expression<numType> operator/(const Expression<numType> &LH, const Expression<numType> &RH){
    Simplifications
    return AbsExp_ptr<numType>(new Division_expr<numType>(LH,RH)); 
}

template<typename numType> Expression<numType> operator/(const numType &LH, const Expression<numType> &RH){
    Simplifications
    return AbsExp_ptr<numType>(new Division_numL<numType>(LH,RH)); 
}

template<typename numType> Expression<numType> operator/(const Expression<numType> &LH, const numType &RH){
    Simplifications
    return AbsExp_ptr<numType>(new Division_numR<numType>(LH,RH)); 
}

}


#undef Simplifications
#endif