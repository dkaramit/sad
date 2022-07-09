#include<iostream>
#include<vector>
#include<cmath>
#include<sad.hpp>

using std::cout;
using std::vector;

int main(){

    sad::Expression x;

    std::map at=sad::at(vector{x},vector{0.}) ;

    /*exp(log(x)) is simplified to x*/
    sad::Expression f0=exp(log(x));
    sad::Expression f1=derivative(exp(log(x)),x);
    sad::Expression f2=derivative(log(exp(x)),x);

    cout<< sad::print_expr(f0)<< "\t" << evaluate(f0,at)  <<"\n";
    cout<< sad::print_expr(f1)<< "\t" << evaluate(f1,at)  <<"\n";
    cout<< sad::print_expr(f2)<< "\t" << evaluate(f2,at)  <<"\n";

    return 0;
}