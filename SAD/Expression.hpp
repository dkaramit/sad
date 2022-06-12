#ifndef Expression_H
#define Expression_H

#include <iostream>
#include <cmath>
#include<memory>
#include<valarray>
#include<type_traits>
#include<utility>

#include<SAD/misc.hpp>
#include<SAD/AbstractExpression.hpp>


namespace sad{

/*The Expression class. This will be the interface to access all other classes.*/
template<typename numType>
class Expression{
    friend class Variable<numType>;//we want the Variable class to have access to expr_ptr in order to know wrt what we differentiate
    
    public:
    ~Expression()=default;
    Expression(){expr_ptr=AbsExp_ptr<numType> (new Variable<numType>); };

    Expression(const Expression &);//copy-constructor
    // Expression(Expression && expr);//move-constructor
    
    Expression(const AbsExp_ptr<numType> &);
    // Expression(AbsExp_ptr<numType> &&);
    
    Expression(const numType &);
    // Expression(numType &&);
    
    static auto constant(const numType &value){return Expression<numType>(value);}
    
    numType evaluate(const map<IDType,numType> &values)const;
    Expression derivative(const IDType &)const;
    
    Expression& operator=(const Expression &);
    // Expression& operator=(Expression &&);

    //if this instance is a variable, return its ID. If it is not, returns 0.
    IDType ID()const{ return expr_ptr->ID(); }

    private:
    AbsExp_ptr<numType> expr_ptr;
};




/*Constructors of Expression*/
template<typename numType> Expression<numType>::Expression(const AbsExp_ptr<numType> &expr_ptr):expr_ptr(expr_ptr){}

template<typename numType> Expression<numType>::Expression(const Expression<numType> &expr):expr_ptr(expr.expr_ptr){}

template<typename numType> Expression<numType>::Expression(const numType &value):expr_ptr(new Constant<numType>(value)){}


/*Assignments of Expression*/
template<typename numType>
Expression<numType>& Expression<numType>::operator=(const Expression &expr){
    expr_ptr=expr.expr_ptr;
    return *this;
}


/*derivative and evaluate of Expression*/
template<typename numType>
Expression<numType> Expression<numType>::derivative(const IDType &wrt)const{
    if(wrt == 0) {return ZERO<numType>;}
    return expr_ptr->derivative(wrt);
}

template<typename numType>
numType Expression<numType>::evaluate(const map<IDType,numType> &values)const{ return expr_ptr->evaluate(values); }



}
#endif