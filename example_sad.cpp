// Example on how to generate expressions and types for sadET

#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;

int main(){
    auto x=sad::Variable(5.);
    auto y=sad::Variable(1.);
    auto expr=sad::Variable(0);

    expr = y*sad::Variable(2) +x ;

    cout<< expr<<"\n";
    cout<< expr->der(x)<<"\n";
    cout<< expr->der(y)<<"\n";

    expr = expr + y*y;

    cout<< expr->der(y)->der(x)<<"\n";
    cout<< expr->der(y)->der(y)<<"\n";


    return 0;
}