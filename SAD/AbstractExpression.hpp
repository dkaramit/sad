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
    virtual numType evaluate(const map<IDType,numType> &)const=0;
    
    virtual Expression<numType> derivative(const IDType &)const=0;
    virtual IDType ID()const{return 0;}
};

template<typename numType>
class Constant:public AbstractExpression<numType>{
    friend class Expression<numType>;
    public:
    Constant(const numType &value):value(value){}

    private:
    numType evaluate(const map<IDType,numType> &)const{return value;};
    Expression<numType> derivative(const IDType &wrt)const{ return ZERO<numType>; }

    numType value;
};



template<typename numType>
class Variable:public AbstractExpression<numType>{
    friend class Expression<numType>;
    public:
    Variable():id(++NumberOfVars){}

    private:
    numType evaluate(const map<IDType,numType> &at)const{
        if (at.find(ID()) == at.end()){throw std::runtime_error( std::string("No value for variable with ID: ") + std::to_string(ID()) ) ;}
        return at.at(ID());
    };

    Expression<numType> derivative(const IDType &wrt)const{
        //check if we differentiate wrt this variable
        if(this->id==wrt){return ONE<numType>;}//if we differentiate wrt the same variable, return an Expression that evaluates to 1
    	return ZERO<numType>;//otherwise, return an Expression that evaluates to 0
    }
    IDType ID()const{return id;}

    const IDType id;
    static IDType NumberOfVars;
};
template<typename numType> IDType Variable<numType>::NumberOfVars=0;


}
#endif