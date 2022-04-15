#ifndef BinOp_H
#define BinOp_H

#include<SAD/declarations.hpp>
#include<SAD/Expression.hpp>


namespace sad{

struct Addition:Expression{
    const std::shared_ptr<Expression> LHS,RHS;
    Addition(const std::shared_ptr<Expression> &LHS, const std::shared_ptr<Expression> &RHS):LHS(LHS),RHS(RHS){};
    double eval() const {return LHS->eval() + RHS->eval();}
    
    std::shared_ptr<Expression> der(std::shared_ptr<Expression> &wrt) const {return LHS->der(wrt) + RHS->der(wrt) ;}

};

struct Multiplication:Expression{
    const std::shared_ptr<Expression> LHS,RHS;
    Multiplication(const std::shared_ptr<Expression> &LHS, const std::shared_ptr<Expression> &RHS):LHS(LHS),RHS(RHS){};
    double eval() const {return LHS->eval() * RHS->eval();}
    
    std::shared_ptr<Expression> der(std::shared_ptr<Expression> &wrt) const {
        return (LHS * RHS->der(wrt)) + (RHS * LHS->der(wrt));
    }

};

std::shared_ptr<Expression> operator+(const std::shared_ptr<Expression> &LHS, const std::shared_ptr<Expression> &RHS){return std::shared_ptr<Expression>( new Addition(LHS,RHS) ); }
std::shared_ptr<Expression> operator*(const std::shared_ptr<Expression> &LHS, const std::shared_ptr<Expression> &RHS){return std::shared_ptr<Expression>( new Multiplication(LHS,RHS) ); }


}


#endif