#ifndef Expression_H
#define Expression_H

#include <iostream>
#include <cmath>
#include<memory>
#include<valarray>
#include<type_traits>

// static size_t _sad_count_=0;
// #define PPF std::cout<<++_sad_count_<<"\t"<<__PRETTY_FUNCTION__<<"\t"<<sad::Expression<numType>::TotalNumberOfVariables()<<"\t"


namespace sad{

template<typename numType> class AbstractExpression;
template<typename numType> class Variable;

template<typename numType>
using AbsExp_ptr=std::shared_ptr<AbstractExpression<numType>>; 

template<typename numType>
class Expression{
    friend class Variable<numType>;//we want the Variable class to have access to expr_ptr in order to know wrt what we differentiate
    public:
    ~Expression()=default;
    Expression()=delete;
    Expression(const Expression &);
    Expression(const AbsExp_ptr<numType> &);
    Expression(const numType &, const bool &is_var=true);
    
    numType evaluate()const;
    Expression derivative(const unsigned int &)const;
    
    Expression* operator=(const numType &);
    Expression* operator=(const Expression &);

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

/*----these constants will be helpful---*/
template<typename numType>static const Expression<numType> ONE(1,false);
template<typename numType>static const Expression<numType> ZERO(0,false);
template<typename numType>static const Expression<numType> NEG_ONE(-1,false);
template<typename numType>static const Expression<numType> HALF(0.5,false);
template<typename numType>static const Expression<numType> PI(M_PI,false);
template<typename numType>static const Expression<numType> PI2(M_PI*M_PI,false);
template<typename numType>static const Expression<numType> SQRT_PI(2/M_2_SQRTPI,false);


template<typename numType>
class AbstractExpression{
    friend class Expression<numType>;
	public:
    virtual ~AbstractExpression()=default;
    AbstractExpression()=default;
    
    private:
    virtual numType evaluate()const=0;
    virtual Expression<numType> derivative(const unsigned int &id)const=0;
};

template<typename numType>
class Variable:public AbstractExpression<numType>{
    friend class Expression<numType>;
    public:
    Variable(const numType &value, const unsigned int &id=0):value(value),id(id){}//id==0 means a constant

    private:
    numType evaluate()const{return this->value;}
    Expression<numType> derivative(const unsigned int &wrt)const{
        //check if we differentiate wrt this variable
        if(this->id==wrt){return ONE<numType>;}//if we differentiate wrt the same variable, return an Expression that evaluates to 1
    	return ZERO<numType>;//otherwise, return an Expression that evaluates to 0
    }
    numType value;
    unsigned int id;
};


/*Constructors of Expression*/
template<typename numType>
Expression<numType>::Expression(const AbsExp_ptr<numType> &expr_ptr):expr_ptr(expr_ptr),is_var(false){}
template<typename numType>
Expression<numType>::Expression(const Expression<numType> &expr):expr_ptr(expr.expr_ptr){
    
    if(not expr.isVar()){ is_var=false;} // if expr is not a varialbe, then the new expression is not a variable  
    if(expr.isVar()){is_var=true; getVar()->id=expr.getVar()->id; } //if expr is a variable, then then the new expression becomes an alias for expr. The number of variables stays the same. 
}

template<typename numType>
Expression<numType>::Expression(const numType &value, const bool &is_var):expr_ptr(new Variable<numType>(value,0)),is_var(is_var){
    //when the new instance is as variable (is_var=true), we increase NumberOfVars and make this number the id of the new variable.
    if(is_var){getVar()->id = ++Expression<numType>::NumberOfVars;}
}

/*Assignments of Expression*/
template<typename numType>
Expression<numType>* Expression<numType>::operator=(const Expression &expr){
    
    //the new expression becomes the AbstractExpression pointer from expr.
    expr_ptr=expr.expr_ptr;
    /*These are the same as the corresponding constructor*/
    if(not expr.isVar()){ is_var=false;} // if expr is not a varialbe, then the new expression is not a variable  
    if(expr.isVar()){ is_var=true; getVar()->id=expr.getVar()->id; } //if expr is a variable, then then the new expression becomes an alias for expr. The number of variables stays the same. 

    return this;
}

template<typename numType>
Expression<numType>* Expression<numType>::operator=(const numType &value){
    
    //if this expression is already a variable, then just chage its value
    if (isVar()) {getVar()->value=value; }

    //if this expression is not a variable, then make it a new variable. This means that NumberOfVars is increased
    // and its id gets the new NumberOfVars number.
    if(not isVar()){
        expr_ptr = std::shared_ptr<Variable<numType>>(new Variable<numType>(value));
        is_var=true;
        getVar()->id= ++Expression<numType>::NumberOfVars;
    }
    return this;
}


/*derivative and evaluate of Expression*/
template<typename numType>
Expression<numType> Expression<numType>::derivative(const unsigned int &wrt)const{
    if(wrt == 0) {return ZERO<numType>;}
    return expr_ptr->derivative(wrt);
}

template<typename numType>
numType Expression<numType>::evaluate()const{ return expr_ptr->evaluate(); }




/*You can use these functions to take the derivative easier*/

//derivative with respect to a variable (it takes the id of the variable as unsigned it)
template<typename numType>Expression<numType> derivative(const Expression<numType> &Expr, const unsigned int &wrt){return Expr.derivative(wrt);}

//derivative with respect to a valarray of ids
template<typename numType> Expression<numType> derivative(const Expression<numType> &Expr, const std::valarray<unsigned int> &wrt){
    std::valarray<unsigned int>  tail= wrt[ std::slice(1, wrt.size() - 1, 1) ];
    if(wrt.size() == 1 ){return Expr.derivative(wrt[0]) ; }
    return  derivative( Expr.derivative(wrt[0]) , tail ) ;
}

//this does the same as derivative(const Expression<numType> &Expr, const std::valarray<unsigned int> &wrt), but you can call it
// using a parameter pack of instances of Expression
template<typename numType,typename... Args>
Expression<numType> derivative(const Expression<numType> &Expr, const Args&... vars){ return  derivative(Expr, std::valarray<unsigned int>{vars.ID()...}) ;}







}
#endif