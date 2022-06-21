#include<iostream>
#include<sad.hpp>

using std::cout;

using LD = double;

int main(){

    sad::Expression<LD> x,y;
    sad::Expression z=x;

    z=sad::cos(x / sin(y));

    std::map at=sad::at(std::vector{x,y},std::vector{6,2}) ;

    cout<<evaluate(z, at )<<"\n";
    cout<<evaluate(derivative(z,x), at )<<"\n";
    cout<<evaluate(derivative(z,y), at )<<"\n";


    cout<<evaluate(derivative(z,x,y,x,x,x), at )<<"\n";


    return 0;
}