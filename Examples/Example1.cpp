#include<iostream>
#include<sad.hpp>

using std::cout;

using LD = double;

int main(){

    sad::Expression<LD> x,y;
    sad::Expression z=x+y*x;

    std::map at=sad::at(std::vector{x,y},std::vector{6,2}) ;
    
    cout<<evaluate(x, at )<<"\n";
    cout<<evaluate(derivative(x,x), at )<<"\n";
    cout<<evaluate(derivative(x,y), at )<<"\n";


    cout<<evaluate(y, at )<<"\n";
    cout<<evaluate(derivative(y,x), at )<<"\n";
    cout<<evaluate(derivative(y,y), at )<<"\n";


    cout<<evaluate(z, at )<<"\n";
    cout<<evaluate(derivative(z,x), at )<<"\n";
    cout<<evaluate(derivative(z,y), at )<<"\n";


    return 0;
}