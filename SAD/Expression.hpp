#ifndef ExpressionType_H
#define ExpressionType_H

#include<memory>


namespace sad{

template<typename numType> struct Expression;
template<typename numType> struct AbstractExpression;
template<typename numType> struct Variable;

template<typename numType>
struct  Expression{
    Expression(const Expression &expr);
    Expression(AbstractExpression<numType> *);
    explicit Expression(const numType &);
    
    Expression der(const Expression<numType> &);
    numType eval();
    Expression* operator=(const Variable<numType> &);
    
    private:
    AbstractExpression<numType> *expr_ptr;
};

template<typename numType>
struct AbstractExpression{
    friend struct Expression<numType>;
    private:
    virtual numType eval()=0;
    virtual Expression<numType> der(const Expression<numType> &)=0;
};

template<typename numType>
struct Variable:public AbstractExpression<numType>{
    Variable(const numType &value):value(value){}
    friend struct Expression<numType>;

    private:
    numType eval(){return value;}
    Expression<numType> der(const Expression<numType> &var){
    	return Expression<numType>( numType(1) );
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
Expression<numType> Expression<numType>::der(const Expression<numType> &var){ return expr_ptr->der(var); }
template<typename numType>
Expression<numType>* Expression<numType>::operator=(const Variable<numType> &var){ static_cast<Variable<numType>*>(expr_ptr)->value=var.value; return this;}
template<typename numType>
numType Expression<numType>::eval(){ return expr_ptr->eval(); }

template<typename numType>
struct ADD: public AbstractExpression<numType>{
    ADD(const Expression<numType> &LH, const Expression<numType> &RH):LH(LH),RH(RH){}
    friend struct Expression<numType>;
    private:
    Expression<numType> LH,RH;
    Expression<numType> der(const Expression<numType> &);
    numType eval();
};
/*this is the addition operator*/
template<typename numType>
Expression<numType> operator+(const Expression<numType> &LH, const Expression<numType> &RH){return static_cast<AbstractExpression<numType>*>(new ADD<numType>(LH,RH));}

/*This need to be after operator+ has been declared.*/
template<typename numType>
Expression<numType> ADD<numType>::der(const Expression<numType> &var){return LH.der(var)+RH.der(var);}
template<typename numType>
numType ADD<numType>::eval(){ return LH.eval()+RH.eval(); }

}
#endif