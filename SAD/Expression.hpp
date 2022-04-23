#ifndef Expression_H
#define Expression_H

#include <iostream>
#include<memory>
#include<type_traits>

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
    Expression(const numType &);
    Expression(const AbsExp_ptr<numType> &);
    
    numType evaluate()const;
    Expression derivative(const Expression<numType> &)const;
    
    Expression* operator=(const numType &);
    Expression* operator=(const Expression &);

    /*overload the ostream so that it prints the evaluated result*/
    friend std::ostream& operator<<(std::ostream& os, const Expression &expr){
        os << expr.evaluate() ;
        return os;
    }

    void status()const{std::cout<<bool(is_var)<<"\n";}

    private:
    AbsExp_ptr<numType> expr_ptr;
    bool is_var;
};

template<typename numType>
class AbstractExpression{
    friend class Expression<numType>;
	public:
    virtual ~AbstractExpression()=default;
    AbstractExpression()=default;
    
    private:
    virtual numType evaluate()const=0;
    virtual Expression<numType> derivative(const Expression<numType> &)const=0;
};

template<typename numType>
class Variable:public AbstractExpression<numType>{
    friend class Expression<numType>;
    public:
    Variable(const numType &value):value(value){}

    private:
    numType evaluate()const{return this->value;}
    Expression<numType> derivative(const Expression<numType> &wrt)const{
        //check if we differentiate wrt this variable
        if(this==wrt.expr_ptr.get()){return Expression<numType>( numType(1) );}//if we differentiate wrt the same variable, return an Expression that evaluates to 1
    	return Expression<numType>( numType(0) );//otherwise, return an Expression that evaluates to 0
    }
    numType value;
};


/*The friend class depends on all the others, so put the definitions down here*/
template<typename numType>
Expression<numType>::Expression(const Expression<numType> &expr):expr_ptr(expr.expr_ptr),is_var(0){}
template<typename numType>
Expression<numType>::Expression(const AbsExp_ptr<numType> &expr_ptr):expr_ptr(expr_ptr),is_var(0){}
template<typename numType>
inline Expression<numType>* Expression<numType>::operator=(const Expression &expr){
    expr_ptr=expr.expr_ptr;
    is_var=0;

    return this;
}

template<typename numType>
Expression<numType>::Expression(const numType &value):expr_ptr(new Variable<numType>(value)),is_var(1){}

template<typename numType>
inline Expression<numType>* Expression<numType>::operator=(const numType &value){
    if(not is_var){
        expr_ptr = std::shared_ptr<Variable<numType>>(new Variable<numType>(value));
        is_var=1;
    }
    static_cast< Variable<numType>* >(expr_ptr.get())->value=value;    
    return this;
}


template<typename numType>
Expression<numType> Expression<numType>::derivative(const Expression<numType> &wrt)const{
    if(wrt.is_var){return expr_ptr->derivative(wrt);}
    return Expression<numType>( numType(0) );
}

template<typename numType>
numType Expression<numType>::evaluate()const{ return expr_ptr->evaluate(); }



}
#endif