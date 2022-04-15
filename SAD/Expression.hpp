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
    virtual Expression<numType> der(Expression<numType> &wrt) const =0;
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
    numType & eval() {return val;}
    
    Expression<numType> der(Expression<numType> &wrt) const {
        if(wrt.get()==this){return Variable<numType>( static_cast<numType>(1) );}
        return Variable<numType>(static_cast<numType>(0));
    }
};

template<typename numType>
Expression<numType> Variable(const numType &x){return Expression<numType>(new VariableType<numType>(x));}


}
#endif