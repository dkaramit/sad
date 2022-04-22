#ifndef Expression_H
#define Expression_H

#include <iostream>
#include<memory>
#include<valarray>

namespace sad{

template<typename numType> class AbstractExpression;
template<typename numType> class Variable;

template<typename numType>
using AbsExp_ptr=std::shared_ptr<AbstractExpression<numType>>; 

template<typename numType>
class  Expression{
    public:
    ~Expression()=default;
    Expression(const Expression &expr);
    Expression(const AbsExp_ptr<numType> &);
    explicit Expression(const numType &);
    
    Expression derivative(const Expression<numType> &)const;
    numType evaluate()const;
    Expression* operator=(const numType &);

    /*overload the ostream so that it prints the evaluated result*/
    friend std::ostream& operator<<(std::ostream& os, const Expression &expr){
        os << expr.evaluate() ;
        return os;
    }

    friend class Variable<numType>;//we want the Variable class to have access to expr_ptr in order to know wrt what we differentiate
    private:
    AbsExp_ptr<numType> expr_ptr;
};

template<typename numType>
class AbstractExpression{
	public:
    virtual ~AbstractExpression()=default;
    AbstractExpression()=default;
    friend class Expression<numType>;
    private:
    virtual numType evaluate()const=0;
    virtual Expression<numType> derivative(const Expression<numType> &)const=0;
};
template<typename numType>
class Variable:public AbstractExpression<numType>{
    public:
    Variable(const numType &value):value(value){}
    friend class Expression<numType>;

    private:
    numType evaluate()const{return value;}
    Expression<numType> derivative(const Expression<numType> &wrt)const{
        //check if we differentiate wrt this variable
        if(this==wrt.expr_ptr.get()){return Expression<numType>( numType(1) );}//if we differentiate wrt the same variable, return an Expression that evaluates to 1
    	return Expression<numType>( numType(0) );//otherwise, return an Expression that evaluates to 0
    }
    numType value;
};


/*The friend class depends on all the others, so put the definitions down here*/
template<typename numType>
Expression<numType>::Expression(const Expression<numType> &expr):expr_ptr(expr.expr_ptr){}
template<typename numType>
Expression<numType>::Expression(const numType &value):expr_ptr(new Variable<numType>(value)){}
template<typename numType>
Expression<numType>::Expression(const AbsExp_ptr<numType> &expr_ptr):expr_ptr(expr_ptr){}
template<typename numType>
Expression<numType> Expression<numType>::derivative(const Expression<numType> &wrt)const{ return expr_ptr->derivative(wrt); }

template<typename numType>
Expression<numType>* Expression<numType>::operator=(const numType &value){
    static_cast< Variable<numType>* >(expr_ptr.get())->value=value;
    return this;
}

template<typename numType>
numType Expression<numType>::evaluate()const{ return expr_ptr->evaluate(); }




/*functions to get the derivates and evaluate the expressions*/
template<typename numType>Expression<numType> derivative(const Expression<numType> &Expr, const Expression<numType> &wrt){return Expr.derivative(wrt);}

template<typename numType> Expression<numType> derivative(const Expression<numType> &Expr, const std::valarray<Expression<numType>> &wrt){
    std::valarray<Expression<numType>>  tail = wrt[ std::slice(1, wrt.size() - 1, 1) ];
    if(wrt.size() == 1 ){return Expr.derivative(wrt[0]) ; }
    return  derivative(Expr.derivative(wrt[0]), tail ) ;
}

template<typename numType> auto evaluate(const Expression<numType> &Expr){return Expr.evaluate();}

}
#endif