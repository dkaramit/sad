#ifndef BinOp_H
#define BinOp_H

#include <cmath> 

#include<SAD/declarations.hpp>


namespace sad{

template<typename numType>
struct Addition:ExpressionType<numType>{
    const Expression<numType> LHS,RHS;
    Addition(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){};
    numType eval() const {return LHS->eval() + RHS->eval();}
    
    Expression<numType> der(const Expression<numType> &wrt) const {return LHS->der(wrt) + RHS->der(wrt) ;}

};
template<typename numType>
struct Subtruction:ExpressionType<numType>{
    const Expression<numType> LHS,RHS;
    Subtruction(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){};
    numType eval() const {return LHS->eval() - RHS->eval();}
    Expression<numType> der(const Expression<numType> &wrt) const {return LHS->der(wrt) - RHS->der(wrt) ;}
};



template<typename numType>
struct Multiplication:ExpressionType<numType>{
    const Expression<numType> LHS,RHS;
    Multiplication(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){};
    numType eval() const {return LHS->eval() * RHS->eval();}
    Expression<numType> der(const Expression<numType> &wrt) const {
        return (LHS * RHS->der(wrt)) + (RHS * LHS->der(wrt));
    }
};

template<typename numType>
struct Division:ExpressionType<numType>{
    const Expression<numType> LHS,RHS;
    Division(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){};
    numType eval() const {return LHS->eval() / RHS->eval();}
    Expression<numType> der(const Expression<numType> &wrt) const {
        return LHS->der(wrt)/RHS - LHS*(RHS->der(wrt))/(RHS*RHS) ;
    }
};

template<typename numType>
struct Pow:ExpressionType<numType>{
    const Expression<numType> LHS,RHS;
    Pow(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){};
    numType eval() const {return  std::pow(LHS->eval(),RHS->eval());}
    Expression<numType> der(const Expression<numType> &wrt) const {
        /*if the derivative of the RHS is zero, the logarithm should not appear!*/
        if(RHS->der(wrt)->eval() == static_cast<numType>(0) ){return pow( LHS,RHS - Variable<numType>(1) ) * RHS*LHS->der(wrt);}
        return  pow( LHS,RHS - Variable<numType>(1) ) * (RHS*LHS->der(wrt) + LHS*log(LHS)*RHS->der(wrt) );
    }
};


DefineNewBinaryOperator(operator+,Addition)
DefineNewBinaryOperator(operator*,Multiplication)
DefineNewBinaryOperator(operator-,Subtruction)
DefineNewBinaryOperator(operator/,Division)
DefineNewBinaryOperator(pow,Pow)

}


#endif