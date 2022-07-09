#include<iostream>
#include<sad.hpp>

using std::cout;




int main(){

    sad::Expression x,y;
    auto c=sad::Expression<double>::constant(2.);
    sad::Expression z=sin(x*y);

    std::map at=sad::at(std::vector{x,y},std::vector{0.325,3.}) ;
    
    // cout<<sad::evaluate( derivative(z,x),at )<<"\n";

    cout<<sad::functions_generation(std::vector{x,y},std::vector{z,derivative(z,x)})<<"\n";
    cout<<sad::class_generation("test",std::vector{x,y},std::vector{z,derivative(z,x)})<<"\n";
    
    return 0;
}