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
    Expression()=delete;

    Expression(const Expression &);//copy-constructor
    // Expression(Expression && expr);//move-constructor
    
    Expression(const AbsExp_ptr<numType> &);
    // Expression(AbsExp_ptr<numType> &&);

    Expression(const numType &, const bool &is_var=true);
    // Expression(numType &&, bool &&is_var=true);
    static auto variable(const numType &value){return Expression<numType>(value);}
    static auto constant(const numType &value){return Expression<numType>(value,false);}
    
    numType evaluate()const;
    Expression derivative(const IDType &)const;
    
    Expression& operator=(const numType &);
    // Expression& operator=(numType &&);

    Expression& operator=(const Expression &);
    // Expression& operator=(Expression &&);

    /*overload the ostream so that it prints the evaluated result*/
    friend std::ostream& operator<<(std::ostream& os, const Expression &expr){
        os <<expr.evaluate() ;
        return os;
    }

    //returns if this instance is a variable
    bool isVar()const{return is_var;}
    
    //if this instance is a variable, return its ID. If it is not, returns 0.
    IDType ID()const{ return expr_ptr->ID(); }
    

    static IDType  TotalNumberOfVariables(){ return Variable<numType> :: NumberOfVars;}
    private:
    AbsExp_ptr<numType> expr_ptr;
    const bool is_var;

    //Get the raw pointer to the expr_ptr casted as Variable<numType>*. 
    //This is private as it will only be used within this class, and only with
    //extreme care. 
    Variable<numType>* getVar()const{ return static_cast< Variable<numType>* >(expr_ptr.get()); }
};




/*Constructors of Expression*/
template<typename numType> Expression<numType>::Expression(const AbsExp_ptr<numType> &expr_ptr):expr_ptr(expr_ptr),is_var(false){}

template<typename numType>
Expression<numType>::Expression(const Expression<numType> &expr):expr_ptr(expr.expr_ptr), is_var(false){}

template<typename numType>
Expression<numType>::Expression(const numType &value, const bool &is_var):expr_ptr(new Variable<numType>(value,is_var)),is_var(is_var){}


/*Assignments of Expression*/
template<typename numType>
Expression<numType>& Expression<numType>::operator=(const Expression &expr){
    
    //If this instance is a variable, assign the value o the expression to this variable
    if(isVar()){  getVar()->value= expr.evaluate(); }
    
    //if it is not then it becomes the expression (ie the expr_ptr is copied).
    if(not isVar()){ expr_ptr=expr.expr_ptr; } 
    
    return *this;
}

template<typename numType>
Expression<numType>& Expression<numType>::operator=(const numType &value){
   
    //if this instance is a variable, its value changes
    if (isVar()) { getVar()->value=value; }
   
    //if it is not, throw an exception!
    if(not isVar()){  throw std::runtime_error("You cannot assign number to Expression!") ; }
   
    return *this;
}


/*derivative and evaluate of Expression*/
template<typename numType>
Expression<numType> Expression<numType>::derivative(const IDType &wrt)const{
    if(wrt == 0) {return ZERO<numType>;}
    return expr_ptr->derivative(wrt);
}

template<typename numType>
numType Expression<numType>::evaluate()const{ return expr_ptr->evaluate(); }



}
#endif