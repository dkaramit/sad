#include<iostream>
#include<sad.hpp>

using std::cout;

int main(){

    // sad::Expression<long double> x,y;
    sad::Expression x,y;
    sad::Expression z=sad::tanh(x);

    std::map at=sad::at(std::vector{x,y},std::vector{2,3.1}) ;

    z=1.-z-1./y/x/1. -1. ;
    z=z+x;
    z=z*y;
    z=sad::sin(z/y);
    z=sad::exp(sad::abs( z )*2.);

    cout<<evaluate(z, at )<<"\n";
    cout<<evaluate(derivative(z,x), at )<<"\n";
    cout<<evaluate(derivative(z,y), at )<<"\n";
    cout<<evaluate(derivative(z,x,y,x,x), at )<<"\n";
    
    return 0;
}