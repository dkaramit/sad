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
    
    Expression(const numType &, const bool &is_var=true);
    // Expression(numType &&, bool &&is_var=true);
    
    Expression(const AbsExp_ptr<numType> &);
    // Expression(AbsExp_ptr<numType> &&);
    
    numType evaluate()const;
    Expression derivative(const unsigned int &)const;
    
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
    unsigned int ID()const{ 
        if(isVar()){return getVar()->id;}
        return 0;
    }
    

    static unsigned int  TotalNumberOfVariables(){ return NumberOfVars;}
    private:
    AbsExp_ptr<numType> expr_ptr;
    bool is_var;
    static unsigned int NumberOfVars;

    //Get the raw pointer to the expr_ptr casted as Variable<numType>*. 
    //This is private as it will only be used within this class, and only with
    //extreme care. 
    Variable<numType>* getVar()const{ return static_cast< Variable<numType>* >(expr_ptr.get()); }
};

template<typename numType> unsigned int Expression<numType>::NumberOfVars=0;



/*Constructors of Expression*/
template<typename numType> Expression<numType>::Expression(const AbsExp_ptr<numType> &expr_ptr):expr_ptr(expr_ptr),is_var(false){}

template<typename numType>
Expression<numType>::Expression(const Expression<numType> &expr):expr_ptr(expr.expr_ptr){
    if(not expr.isVar()){is_var=false;} // if expr is not a varialbe, then the new expression is not a variable  
    if(expr.isVar()){is_var=true; getVar()->id= expr.ID() ; } //if expr is a variable, then then the new expression becomes an alias for expr. The number of variables stays the same. 
}

template<typename numType>
Expression<numType>::Expression(const numType &value, const bool &is_var):expr_ptr(new Variable<numType>(value,0)),is_var(is_var){
    //when the new instance is as variable (is_var=true), we increase NumberOfVars and make this number the id of the new variable.
    if(is_var){getVar()->id = ++Expression<numType>::NumberOfVars;}
}


/*Assignments of Expression*/
template<typename numType>
Expression<numType>& Expression<numType>::operator=(const Expression &expr){
    //the new expression becomes the AbstractExpression pointer from expr.
    expr_ptr=expr.expr_ptr;
    /*These are the same as the corresponding constructor*/
    if(not expr.isVar()){ is_var=false;} // if expr is not a varialbe, then the new expression is not a variable  
    if(expr.isVar()){ is_var=true; getVar()->id=expr.getVar()->id; } //if expr is a variable, then then the new expression becomes an alias for expr. The number of variables stays the same. 

    return *this;
}

/*Assignments of Expression*/

template<typename numType>
Expression<numType>& Expression<numType>::operator=(const numType &value){
    expr_ptr = std::shared_ptr<Variable<numType>>(new Variable<numType>(value,ID()));
    
    //if this expression is already a variable, then just chage its value
    if (isVar()) {getVar()->value=value; }

    //if this expression is not a variable, then make it a new variable. This means that NumberOfVars is increased
    // and its id gets the new NumberOfVars number.
    if(not isVar()){
        // expr_ptr = std::shared_ptr<Variable<numType>>(new Variable<numType>(value));
        is_var=true;
        getVar()->id= ++Expression<numType>::NumberOfVars;
    }
    return *this;
}


/*derivative and evaluate of Expression*/
template<typename numType>
Expression<numType> Expression<numType>::derivative(const unsigned int &wrt)const{
    if(wrt == 0) {return ZERO<numType>;}
    return expr_ptr->derivative(wrt);
}

template<typename numType>
numType Expression<numType>::evaluate()const{ return expr_ptr->evaluate(); }



}
#endif