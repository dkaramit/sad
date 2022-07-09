#include<iostream>
#include<vector>
#include<cmath>
#include<sad.hpp>

using std::cout;
using std::vector;

int main(){

    sad::Expression x;

    std::map at=sad::at(vector{x},vector{0.}) ;


    cout<< evaluate(derivative(exp(log(x)),x),at)  <<"\n";

    return 0;
}