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
    AbstractExpression(const AbstractExpression &)=default;
    AbstractExpression(AbstractExpression &&)=default;
    AbstractExpression& operator=(const AbstractExpression &)=delete;
    AbstractExpression& operator=(AbstractExpression &&)=delete;
    
    private:
    virtual numType evaluate(const map<IDType,numType> &)const=0;
    virtual Expression<numType> derivative(const IDType &)const=0;
    virtual bool is_CONST()const=0;
    virtual IDType ID()const{return 0;}

};

template<typename numType>
class Constant:public AbstractExpression<numType>{
    friend class Expression<numType>;
    public:
    ~Constant()=default;
    Constant()=delete;
    Constant& operator=(const Constant &)=delete;
    Constant& operator=(Constant &&)=delete;


    private:
    Constant(const numType &value):value(value){}
    Constant(numType &&value):value(value){}

    bool is_CONST()const{return true;}

    numType evaluate(const map<IDType,numType> &)const{return value;};
    Expression<numType> derivative(const IDType &wrt)const{ return ZERO<numType>; }
    const numType value;
};



template<typename numType>
class Variable:public AbstractExpression<numType>{
    friend class Expression<numType>;
    public:
    ~Variable()=default;
    Variable(const Variable &)=delete;
    Variable(Variable &&)=delete;
    Variable& operator=(const Variable &)=delete;
    Variable& operator=(Variable &&)=delete;


    private:
    Variable():id(++NumberOfVars){}

    numType evaluate(const map<IDType,numType> &at)const{
        if (at.find(ID()) == at.end()){throw std::runtime_error( std::string("No value for variable with ID: ") + std::to_string(ID()) ) ;}
        return at.at(ID());
    };

    Expression<numType> derivative(const IDType &wrt)const{ return wrt == ID() ? ONE<numType> : ZERO<numType>; }
    IDType ID()const{return id;}
    bool is_CONST()const{return false;}

    const IDType id;
    static IDType NumberOfVars;
};
template<typename numType> IDType Variable<numType>::NumberOfVars=0;


}
#endif