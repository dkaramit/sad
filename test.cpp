#include<iostream>
#include<sad.hpp>

using std::cout;



int main(){

    // sad::Expression<long double> x,y;
    sad::Expression x,y;
    sad::Expression z=x;


    std::map at=sad::at(std::vector{x,y},std::vector{1.,4.1}) ;
    
    // z=sad::abs(sad::cos(x/sad::sin(y))) ;
    // z=sad::pow(sad::abs(sad::sin(3.+x)),y) ;
    z=sad::pow(x,sad::abs(x)+y) ;

    cout<<evaluate(z, at )<<"\n";
    cout<<evaluate(derivative(z,x), at )<<"\n";
    cout<<evaluate(derivative(z,y), at )<<"\n";

    cout<<evaluate(derivative(z,x,y,x,x,y), at )<<"\n";

    return 0;
}