#ifndef ExpressionType_H
#define ExpressionType_H

#include<memory>


namespace sad{
constexpr char empty_char[]="";//use this for everything except variables

template<typename numType> struct Expression;
template<typename numType> struct AbstractExpression;
template<typename numType> struct Variable;

template<typename numType>
struct  Expression{
		~Expression()=default;
    Expression(const Expression &expr);
    Expression(AbstractExpression<numType> *);
    explicit Expression(const numType &, const char *name=empty_char);
    
    Expression der(const Expression<numType> &)const;
    numType eval()const;
    Expression* operator=(const Variable<numType> &);
    
    const char* symbol()const{return expr_ptr->symbol();}
    
    private:
    AbstractExpression<numType> *expr_ptr;
};

template<typename numType>
struct AbstractExpression{
	
		virtual ~AbstractExpression()=default;
		AbstractExpression()=default;
		AbstractExpression(const char *name=empty_char):name(name){}
    friend struct Expression<numType>;
    const char* symbol()const{return name;} 
    private:
    virtual numType eval()const=0;
    virtual Expression<numType> der(const Expression<numType> &)const=0;
    const char* name;
};
template<typename numType>
struct Variable:public AbstractExpression<numType>{
    Variable(const numType &value, const char *name=empty_char):AbstractExpression<numType>(name),value(value){}
    friend struct Expression<numType>;

    private:
    numType eval()const{return value;}
    Expression<numType> der(const Expression<numType> &var)const{
    	if(this->symbol() == empty_char or this->symbol() != var.symbol()){return Expression<numType>( numType(0) , empty_char);}
    	return Expression<numType>( numType(1) , empty_char);
    }
    numType value;
};


/*The friend class depends on all the others, so put the definitions down here*/
template<typename numType>
Expression<numType>::Expression(const Expression<numType> &expr):expr_ptr(expr.expr_ptr){}
template<typename numType>
Expression<numType>::Expression(const numType &value, const char *name):expr_ptr(new Variable<numType>(value,name)){}
template<typename numType>
Expression<numType>::Expression(AbstractExpression<numType> *expr_ptr):expr_ptr(expr_ptr){}
template<typename numType>
Expression<numType> Expression<numType>::der(const Expression<numType> &var)const{ return expr_ptr->der(var); }
template<typename numType>
Expression<numType>* Expression<numType>::operator=(const Variable<numType> &var){ static_cast<Variable<numType>*>(expr_ptr)->value=var.value;static_cast<Variable<numType>*>(expr_ptr)->name=var.name; return this;}
template<typename numType>
numType Expression<numType>::eval()const{ return expr_ptr->eval(); }

template<typename numType>
struct ADD: public AbstractExpression<numType>{
    ADD(const Expression<numType> &LH, const Expression<numType> &RH):AbstractExpression<numType>(empty_char),LH(LH),RH(RH){}
    friend struct Expression<numType>;
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
Expression<numType> ADD<numType>::der(const Expression<numType> &var)const{return LH.der(var)+RH.der(var);}
template<typename numType>
numType ADD<numType>::eval()const{ return LH.eval()+RH.eval(); }

}
#endif