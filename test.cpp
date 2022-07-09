#include<iostream>
#include<vector>
#include<cmath>
#include<sad.hpp>

using std::cout;
using std::vector;

int main(){

    sad::Expression<long double> x,y;
    sad::Expression z=x*y;
    z=sin(z);
    z=exp(z);

    sad::Expression f=derivative(z,x,y);

    cout<<sad::functions_generation(vector{x,y,x,x},vector{z,derivative(z,x),derivative(z,y),f})<<"\n";


    cout<<sad::class_generation("Model",vector{y,x,z},vector{z,derivative(z,x),derivative(z,y),f})<<"\n";
    
    return 0;
}