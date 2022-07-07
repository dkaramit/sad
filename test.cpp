#include<iostream>
#include<sad.hpp>

using std::cout;

int main(){

    sad::Expression x,y;

    std::map at=sad::at(std::vector{x,y},std::vector{0.3,3.}) ;
    
    sad::Expression z=pow(sad::ZERO<double>,0.);

    // sad::Expression z=tan(1./sad::Expression<double>::constant(2.1)/x/sad::Expression<double>::constant(2)/y/1.);
    // z=y/x+z+1.;
    // z=1./z-x;
    // z=z*y;
    // z=sin(z/y);
    // z=exp( z );
    // z=tanh( -z*y );
    // z=log( abs(z)/3. );
    // z=pow(abs(tan(z)),y);

    cout<<evaluate(z, at)<<"\n";

    cout<<evaluate(derivative(z,x), at )<<"\n";
    cout<<evaluate(derivative(z,y), at )<<"\n";

    cout<<evaluate(derivative(z,x,y,x,x,y), at )<<"\n";
    
    return 0;
}