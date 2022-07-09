#ifndef PowOp_H
#define PowOp_H


#include<SAD/Expression.hpp>
#include<SAD/UnaryOperators/BasicUnaryOperators.hpp>
#include<SAD/BinaryOperators/Multiplication.hpp>
#include<SAD/BinaryOperators/Addition.hpp>
#include<SAD/BinaryOperators/Subtruction.hpp>
#include<SAD/utilities.hpp>

#define Simplifications if(is_ZERO(RH)){return ONE<numType>;} if(is_ZERO(LH)){return ZERO<numType>;} if(is_ONE(LH)){return ONE<numType>;} if(is_ONE(RH)){return LH;}


namespace sad{

template<typename numType>
class Power_expr: public AbstractExpression<numType>{ 
    public:
    Power_expr(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    Expression<numType> LH,RH;
    Expression<numType> derivative(const unsigned int &wrt)const{ 
        auto DRH=RH.derivative(wrt);
        auto DLH=LH.derivative(wrt);

        //if the rhs is constant and rhs-1==0, then the result shou be 1
        if(RH.is_CONST()){
            if(RH.evaluate(empty_at<numType>) - static_cast<numType>(1) == static_cast<numType>(0)) {return ONE<numType>;}
        }

        return pow( LH,RH - ONE<numType> ) * ( RH*DLH + LH*log(LH)*DRH ); 
    };
    numType evaluate(const map<IDType,numType> &at)const{return std::pow(LH.evaluate(at), RH.evaluate(at));};
    bool is_CONST()const{return LH.is_CONST() and RH.is_CONST();}
    string str()const{return string("pow(") + print_expr(LH) + string(",") + print_expr(RH) + string(")");}
    string head()const{return str();}
};

template<typename numType>
class Power_num1: public AbstractExpression<numType>{ 
    public:
    Power_num1(const numType &LH,const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    
    numType LH;
    Expression<numType> RH;
    Expression<numType> derivative(const unsigned int &wrt)const{ return pow( LH,RH - ONE<numType> ) *   LH*log(LH)*RH.derivative(wrt); }
    numType evaluate(const map<IDType,numType> &at)const{return std::pow(LH, RH.evaluate(at));}
    bool is_CONST()const{return RH.is_CONST();}
    string str()const{return string("pow(") + print_expr(LH) + string(",") + print_expr(RH) + string(")");}
    string head()const{return str();}
};

template<typename numType>
class Power_num2: public AbstractExpression<numType>{ 
    public:
    Power_num2(const Expression<numType> &LH, const numType &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    
    Expression<numType> LH;
    numType RH;
    Expression<numType> derivative(const unsigned int &wrt)const{ 
        //if rhs-1==0, then the result shou be 1
        if(RH - static_cast<numType>(1) == static_cast<numType>(0)) {return ONE<numType>;}

        return pow( LH,RH - ONE<numType> )*RH*LH.derivative(wrt); 
    }
    numType evaluate(const map<IDType,numType> &at)const{return std::pow(LH.evaluate(at), RH);}
    bool is_CONST()const{return LH.is_CONST();}
    string str()const{return string("pow(") + print_expr(LH) + string(",") + print_expr(RH) + string(")");}
    string head()const{return str();}
};

template<typename numType> Expression<numType> pow(const Expression<numType> &LH, const Expression<numType> &RH){
    Simplifications
    return AbsExp_ptr<numType>(new Power_expr<numType>(LH,RH)); 
}
template<typename numType> Expression<numType> pow(const numType &LH, const Expression<numType> &RH){
    Simplifications
    return AbsExp_ptr<numType>(new Power_num1<numType>(LH,RH)); 
}
template<typename numType> Expression<numType> pow(const Expression<numType> &LH, const numType &RH){
    Simplifications
    return AbsExp_ptr<numType>(new Power_num2<numType>(LH,RH)); 
}

}

#undef Simplifications
#endif