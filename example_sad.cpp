#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;



using LD = double;
int main(){
    // /*This is how you define new variables*/
    sad::Expression<LD> x=5;          
    sad::Expression<LD> y(1);
    sad::Expression<LD> z(1,true);
    //this is a constant
    sad::Expression<LD> c(2,false);
    cout<< x.derivative(x) <<"\n";
    cout<< x.derivative(y) <<"\n";
    cout<< y.derivative(y) <<"\n";
    cout<< y.derivative(x) <<"\n";
    x=y;
    cout<< x.derivative(x) <<"\n";
    cout<< x.derivative(y) <<"\n";
    cout<< y.derivative(y) <<"\n";
    cout<< y.derivative(x) <<"\n";

    cout<< (y+x).ID() <<"\n";



return 0;
}