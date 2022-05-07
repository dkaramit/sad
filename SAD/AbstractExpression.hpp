#ifndef AbsExpression_H
#define AbsExpression_H

#include <iostream>
#include <cmath>
#include<memory>
#include<valarray>
#include<type_traits>
#include<utility>

#include<SAD/misc.hpp>


namespace sad{

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
    Variable(const numType &value, const bool &is_var):value(value),id(is_var ? ++NumberOfVars : 0 ){}

    private:
    numType evaluate()const{return this->value;}
    Expression<numType> derivative(const unsigned int &wrt)const{
        //check if we differentiate wrt this variable
        if(this->id==wrt){return ONE<numType>;}//if we differentiate wrt the same variable, return an Expression that evaluates to 1
    	return ZERO<numType>;//otherwise, return an Expression that evaluates to 0
    }
    numType value;
    const unsigned int id;
    static unsigned int NumberOfVars;
};
template<typename numType> unsigned int Variable<numType>::NumberOfVars=0;


}
#endif