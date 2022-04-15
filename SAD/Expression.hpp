#ifndef Expression_H
#define Expression_H

#include<memory>
#include<SAD/declarations.hpp>


namespace sad{

class Expression{

    public:
    Expression()=default;
    virtual double eval() const =0;
    virtual std::shared_ptr<Expression> der(std::shared_ptr<Expression> &wrt) const =0;

    friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Expression> &Expr){
        os << Expr->eval() ;
        return os;
    }


};


class VariableType:public Expression{
    double val;
    
    public:
    VariableType(const double &val):val(val){}
    
    double eval() const {return val;}
    
    std::shared_ptr<Expression> der(std::shared_ptr<Expression> &wrt) const {
        if(wrt.get()==this){return Variable(1);}
        return Variable(0);
    }
};
std::shared_ptr<Expression> Variable(const double &x){return std::shared_ptr<Expression>(new VariableType(x));}


}
#endif