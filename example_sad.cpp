#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;



using LD = double;
int main(){
    /*This is how you define new variables*/
    sad::Expression<LD> x=5;          
    sad::Expression<LD> y=1;
    sad::Expression<LD> f=x*x+y*y;


    cout<< f.evaluate() << "\n"; 
    cout<< f.derivative(x) << "\n"; 
    cout<< f.derivative(y) << "\n"; 

    cout<< f.derivative(x).derivative(x) << "\n"; 
    cout<< f.derivative(x).derivative(y) << "\n"; 
    cout<< f.derivative(y).derivative(x) << "\n"; 
    cout<< f.derivative(y).derivative(y) << "\n"; 

return 0;
}