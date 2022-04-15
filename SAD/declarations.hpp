#ifndef Declarations_H
#define Declarations_H

#include<memory>
#include<string>

namespace sad{

class Expression;
std::shared_ptr<Expression> Variable(const double &x);
std::shared_ptr<Expression> operator+(const std::shared_ptr<Expression> &, const std::shared_ptr<Expression> &);
std::shared_ptr<Expression> operator*(const std::shared_ptr<Expression> &, const std::shared_ptr<Expression> &);

}






#endif