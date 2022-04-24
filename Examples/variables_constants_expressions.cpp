#include<iostream>
#include<SAD/sad.hpp>

using std::cout;

using LD = double;
int main(){

    // /*This is how you define new variables*/
    sad::Expression<LD> x(10);          
    sad::Expression<LD> y(1);
    // The constructor can take two arguments; its value and a bool. The bool determines if it is a variable or not.
    sad::Expression<LD> z(1,true);
    //this is a constant
    sad::Expression<LD> c(2,false);

    cout<< sad::derivative(x,x) <<"\n";
    x=c;
    cout<< sad::derivative(x,x) <<"\n";

    x=y;
    cout<< sad::derivative(x,x) <<"\n";
    cout<< sad::derivative(y,x) <<"\n";
    cout<< sad::derivative(x,y) <<"\n";
    cout<< sad::derivative(y,y) <<"\n";

    x=x+x;
    cout<< sad::derivative(x,x) <<"\n";
    cout<< sad::derivative(y,x) <<"\n";
    cout<< sad::derivative(x,y) <<"\n";

    return 0;
}