// Example on how to generate expressions and types for sadET

#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;



using LD=double;

int main(){
    auto x=sad::Variable<LD>(1.);
    auto y=sad::Variable<LD>(2.);
    auto expr=sad::Variable<LD>(0);

    expr = x;

    cout<< expr->der(x)<<"\n";
    cout<< -expr<<"\n";

    cout<< (expr)->der(x)<<"\n";
    cout<< (-expr)->der(x)<<"\n";

    cout<<D(expr,x)<<"\n";

    return 0;
}