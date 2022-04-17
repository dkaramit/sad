#ifndef BinOp_H
#define BinOp_H

#include <cmath> 

#include<SAD/declarations.hpp>


namespace sad{

DefineBinaryOperatorClass(operator+,Addition,( LHS->eval() + RHS->eval() ),( LHS->der(wrt) +RHS->der(wrt) ))
DefineBinaryOperatorClass(operator-,Subtruction,( LHS->eval() - RHS->eval() ),( LHS->der(wrt)-RHS->der(wrt) ))
DefineBinaryOperatorClass(operator*,Multiplication,( LHS->eval() * RHS->eval() ),( LHS * RHS->der(wrt) + RHS * LHS->der(wrt) ))
DefineBinaryOperatorClass(operator/,Division,( LHS->eval() / RHS->eval() ),( LHS->der(wrt)/RHS - LHS*(RHS->der(wrt))/(RHS*RHS) ))

/*I don't use the macro, because the derivative is a bit more complicated*/
template<typename numType>
struct Pow:ExpressionType<numType>{
    const Expression<numType> LHS,RHS;
    Pow(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){};
    numType eval() const {return  std::pow(LHS->eval(),RHS->eval());}
    Expression<numType> der(const Expression<numType> &wrt) const {
        /*if the derivative of the RHS is zero, the logarithm should not appear!*/
        if(RHS->der(wrt)->eval() == static_cast<numType>(0) ){return pow( LHS,RHS - One<numType> ) * RHS*LHS->der(wrt);}
        return  pow( LHS,RHS - One<numType> ) * (RHS*LHS->der(wrt) + LHS*log(LHS)*RHS->der(wrt) );
    }
    void assign(const numType &val){};
};
DefineBinaryOperator(pow,Pow)    
template<typename numType> Expression<numType> pow(const numType &LHS, const numType &RHS){return  Variable<numType>( std::pow(LHS,RHS) ) ; }
DefineBinaryOperator(operator^,Pow)    

template<typename numType>
auto log(const Expression<numType> &LHS,const Expression<numType> &RHS){return log(RHS)/log(LHS);}
template<typename numType>
auto log(const numType &LHS,const Expression<numType> &RHS){return log(RHS)/std::log(LHS);}
template<typename numType>
auto log(const Expression<numType> &LHS,const numType &RHS){return std::log(RHS)/log(LHS);}
template<typename numType>
auto log(const numType &LHS,const numType &RHS){return Variable<numType>( std::log(RHS)/std::log(LHS) );}




}


#endif