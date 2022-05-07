#include<iostream>
#include<sad.hpp>

using std::cout;

using LD = double;
int main(){
    // /*This is how you define new variables*/
    sad::Expression<LD> x(10);          
    sad::Expression<LD> y(1);
    sad::Expression<LD> z = 1;
    sad::Expression<LD> c = sad::Expression<LD>::variable(2);

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