#ifndef Declarations_H
#define Declarations_H
#include <valarray> 

/*These macros make the definition of new operators easier*/
#define DefineBinaryOperator(op,expr) template<typename numType> Expression<numType> op(const Expression<numType> &LHS, const Expression<numType> &RHS){return newExpression<numType,expr<numType>>(LHS,RHS); }

#define DefineBinaryOperatorClass(Operator,ClassName,evalFunc,derivFunc)template<typename numType>\
    struct ClassName:ExpressionType<numType>{ \
        const Expression<numType> LHS,RHS; \
        ClassName(const Expression<numType> &LHS, const Expression<numType> &RHS):LHS(LHS),RHS(RHS){}; \
        numType eval() const {return evalFunc;} \
        Expression<numType> der(const Expression<numType> &wrt) const {return  derivFunc;} \
    };\
    DefineBinaryOperator(Operator,ClassName)


#define DefineUnaryOperator(op,expr)template<typename numType> Expression<numType> op(const Expression<numType> &Expr){return newExpression<numType,expr<numType>>( Expr );}
#define DefineUnaryOperatorClass(Operator,ClassName,evalFunc,derivFunc)template<typename numType>\
    struct ClassName:ExpressionType<numType>{ \
        const Expression<numType> Expr; \
        ClassName(const Expression<numType> &Expr):Expr(Expr){}; \
        numType eval() const {return evalFunc;} \
        Expression<numType> der(const Expression<numType> &wrt) const {return  derivFunc;} \
    };\
    DefineUnaryOperator(Operator,ClassName)





namespace sad{


template<typename numType>class ExpressionType;
template<typename numType>class VariableType;

template<typename numType>using Expression = std::shared_ptr<ExpressionType<numType>>;


/*functions that can be used to declare variables and expressions easier (it is better to hide the fact tha everything is a pointer, behind these functions)*/
template<typename numType>Expression<numType> Variable(const numType &x){return Expression<numType>(new VariableType<numType>(x));}
template<typename numType, typename ExprType>Expression<numType> newExpression(const Expression<numType> &Expr){ return Expression<numType>( new ExprType(Expr) );}
template<typename numType, typename ExprType>Expression<numType> newExpression(const Expression<numType> &LHS, const Expression<numType> &RHS){ return Expression<numType>( new ExprType(LHS,RHS) );}


/*functions to get the derivates and evaluate the expressions*/
template<typename numType>Expression<numType> derivative(const Expression<numType> &Expr, const Expression<numType> &wrt){return Expr -> der(wrt);}

template<typename numType>
Expression<numType> derivative(const Expression<numType> &Expr, const std::valarray<Expression<numType>> &wrt){
    std::valarray<Expression<numType>>  tail = wrt[ std::slice(1, wrt.size() - 1, 1) ];
    if(wrt.size() == 1 ){return Expr -> der(wrt[0]) ; }
    return  derivative(Expr -> der(wrt[0]), tail ) ;
}

template<typename numType> auto evaluate(const Expression<numType> &Expr){return Expr->eval();}
}






#endif