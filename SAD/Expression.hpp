#ifndef ExpressionType_H
#define ExpressionType_H

#include<memory>


namespace sad{

template<typename numType> class AbstractExpression;
template<typename numType> class Variable;

template<typename numType>
class  Expression{
    public:
    ~Expression()=default;
    Expression(const Expression &expr);
    Expression(AbstractExpression<numType> *);
    explicit Expression(const numType &);
    
    Expression der(const Expression<numType> &)const;
    numType eval()const;
    Expression* operator=(const Variable<numType> &);
    

    friend class Variable<numType>;//we want the Variable class to have access to expr_ptr in order to know wrt what we differentiate
    private:
    AbstractExpression<numType> *expr_ptr;
};

template<typename numType>
class AbstractExpression{
	public:
    virtual ~AbstractExpression()=default;
    AbstractExpression()=default;
    friend class Expression<numType>;
    private:
    virtual numType eval()const=0;
    virtual Expression<numType> der(const Expression<numType> &)const=0;
};
template<typename numType>
class Variable:public AbstractExpression<numType>{
    public:
    Variable(const numType &value):value(value){}
    friend class Expression<numType>;

    private:
    numType eval()const{return value;}
    Expression<numType> der(const Expression<numType> &wrt)const{
        //check if we differentiate wrt this variable
        if(this==wrt.expr_ptr){return Expression<numType>( numType(1) );}//if we differentiate wrt the same variable, return an Expression that evaluates to 1
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
Expression<numType>::Expression(AbstractExpression<numType> *expr_ptr):expr_ptr(expr_ptr){}
template<typename numType>
Expression<numType> Expression<numType>::der(const Expression<numType> &wrt)const{ return expr_ptr->der(wrt); }
template<typename numType>
Expression<numType>* Expression<numType>::operator=(const Variable<numType> &var){ static_cast<Variable<numType>*>(expr_ptr)->value=var.value;static_cast<Variable<numType>*>(expr_ptr)->name=var.name; return this;}
template<typename numType>
numType Expression<numType>::eval()const{ return expr_ptr->eval(); }

template<typename numType>
class ADD: public AbstractExpression<numType>{
    public:
    ADD(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend class Expression<numType>;
    private:
    Expression<numType> LH,RH;
    Expression<numType> der(const Expression<numType> &)const;
    numType eval()const;
};
/*this is the addition operator*/
template<typename numType>
Expression<numType> operator+(const Expression<numType> &LH, const Expression<numType> &RH){return static_cast<AbstractExpression<numType>*>(new ADD<numType>(LH,RH));}

/*This need to be after operator+ has been declared.*/
template<typename numType>
Expression<numType> ADD<numType>::der(const Expression<numType> &wrt)const{return LH.der(wrt)+RH.der(wrt);}
template<typename numType>
numType ADD<numType>::eval()const{ return LH.eval()+RH.eval(); }

}
#endif