#include<iostream>
#include<sad.hpp>

using std::cout;

using LD = long double;

int main(){

    sad::Expression<LD> x,y;
    sad::Expression z=x;


    std::map at=sad::at(std::vector{x,y},std::vector{0.33,2.}) ;
    
    // z=sad::abs(x,at);
    z=sad::cos(x/sad::sin(y));

    cout<<evaluate(z, at )<<"\n";
    cout<<evaluate(derivative(z,x), at )<<"\n";
    cout<<evaluate(derivative(z,y), at )<<"\n";


    cout<<evaluate(derivative(z,x,y,x,x,x), at )<<"\n";


    return 0;
}