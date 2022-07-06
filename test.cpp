#include<iostream>
#include<sad.hpp>

using std::cout;

int main(){

    sad::Expression x,y;
    sad::Expression z=x;

    std::map at=sad::at(std::vector{x,y},std::vector{-1.,3.}) ;
    
    z=y/x+z+1.;
    z=z-x;
    z=z*y;
    z=sin(z/y);
    z=exp( z );
    z=tanh( -z*y );
    z=log( abs(z)/3. );
    z=pow(abs(tan(z)),y);

    cout<<evaluate(z, at)<<"\n";

    cout<<evaluate(derivative(z,x), at )<<"\n";
    cout<<evaluate(derivative(z,y), at )<<"\n";

    cout<<evaluate(derivative(z,x,y,x,x,y), at )<<"\n";
    
    return 0;
}