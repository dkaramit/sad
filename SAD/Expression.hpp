#ifndef ExpressionType_H
#define ExpressionType_H

#include<memory>
#include<SAD/declarations.hpp>


namespace sad{


template<typename numType>
class ExpressionType{
    public:
    ExpressionType()=default;
    virtual numType eval() const =0;
    virtual Expression<numType> der(const Expression<numType> &wrt) const=0;
    friend std::ostream& operator<<(std::ostream& os, const Expression<numType> &Expr){
        os << Expr->eval() ;
        return os;
    }
};

template<typename numType>
class VariableType:public ExpressionType<numType>{
    numType val;
    public:
    VariableType():val(0){}
    VariableType(const numType &val):val(val){}
    numType eval() const {return val;}
    Expression<numType> der(const Expression<numType> &wrt) const;
};


template<typename numType> static auto Zero   = Variable<numType> ( 0   );
template<typename numType> static auto One    = Variable<numType> ( 1   );
template<typename numType> static auto Two    = Variable<numType> ( 2   );
template<typename numType> static auto Half   = Variable<numType> ( 0.5 );
template<typename numType> static auto Pi     = Variable<numType> ( M_PIl );
template<typename numType> static auto Pi2    = Variable<numType> ( M_PI*M_PI );
template<typename numType> static auto SqrtPi = Variable<numType> ( std::sqrt(M_PIl) );


template<typename numType>
Expression<numType> VariableType<numType>::der(const Expression<numType> &wrt) const {
        if(wrt.get()==this){return One<numType>;}
        return Zero<numType>;
}


}
#endif