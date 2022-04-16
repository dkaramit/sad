#ifndef BinOp_H
#define BinOp_H

#include <cmath> 

#include<SAD/declarations.hpp>


namespace sad{

/*I don't use the macro, because the derivative is a bit more complicated*/
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

DefineBinaryOperatorClass(Addition,( LHS->eval() + RHS->eval() ),( LHS->der(wrt) +RHS->der(wrt) ))
DefineBinaryOperatorClass(Subtruction,( LHS->eval() - RHS->eval() ),( LHS->der(wrt)-RHS->der(wrt) ))
DefineBinaryOperatorClass(Multiplication,( LHS->eval() * RHS->eval() ),( LHS * RHS->der(wrt) + RHS * LHS->der(wrt) ))
DefineBinaryOperatorClass(Division,( LHS->eval() / RHS->eval() ),( LHS->der(wrt)/RHS - LHS*(RHS->der(wrt))/(RHS*RHS) ))

DefineBinaryOperator(operator+,Addition)
DefineBinaryOperator(operator*,Multiplication)
DefineBinaryOperator(operator-,Subtruction)
DefineBinaryOperator(operator/,Division)
DefineBinaryOperator(pow,Pow)

}


#endif