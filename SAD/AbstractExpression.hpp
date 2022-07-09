#ifndef AbsExpression_H
#define AbsExpression_H

#include <iostream>
#include <cmath>
#include<memory>
#include<valarray>
#include<type_traits>
#include<utility>
#include<string>

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

    virtual string str()const=0;
    virtual string head()const=0;
    virtual Expression<numType> subExpr()const=0;
};

template<typename numType>
class Constant:public AbstractExpression<numType>{
    friend class Expression<numType>;
    public:
    ~Constant()=default;
    Constant()=delete;
    // Constant(const Constant &)=delete;
    Constant(Constant &&)=delete;

    Constant& operator=(const Constant &)=delete;
    Constant& operator=(Constant &&)=delete;


    private:
    Constant(const numType &value):value(value){}
    Constant(numType &&value):value(value){}
    Constant(const Constant &c):value(c.value){}

    bool is_CONST()const{return true;}
    
    string str()const{return to_string(value);}
    string head()const{return str();}
    Expression<numType> subExpr()const{return AbsExp_ptr<numType>( shared_ptr<Constant>(new Constant(*this)) );}
    
    numType evaluate(const map<IDType,numType> &)const{return value;};
    Expression<numType> derivative(const IDType &wrt)const{ return ZERO<numType>; }
    const numType value;
};



template<typename numType>
class Variable:public AbstractExpression<numType>{
    friend class Expression<numType>;
    public:
    ~Variable()=default;
    // Variable(const Variable &)=delete;
    Variable(Variable &&)=delete;
    Variable& operator=(const Variable &)=delete;
    Variable& operator=(Variable &&)=delete;


    private:
    Variable():id(++NumberOfVars){}
    Variable(const Variable &var):id(var.id){}

    numType evaluate(const map<IDType,numType> &at)const{
        if (at.find(ID()) == at.end()){throw std::runtime_error( std::string("No value for variable with ID: ") + std::to_string(ID()) ) ;}
        return at.at(ID());
    };

    Expression<numType> derivative(const IDType &wrt)const{ return wrt == ID() ? ONE<numType> : ZERO<numType>; }
    IDType ID()const{return id;}
    bool is_CONST()const{return false;}

    string str()const{return string("var_") + std::to_string(id);}
    string head()const{return str();}
    Expression<numType> subExpr()const{return AbsExp_ptr<numType>( shared_ptr<Variable>(new Variable(*this)) );}

    const IDType id;
    static IDType NumberOfVars;
};
template<typename numType> IDType Variable<numType>::NumberOfVars=0;


}
#endif