#include<iostream>
#include<complex>
#include<sad.hpp>

using std::cout;

using numT=std::complex<double>;

int main(){

    // sad::Expression<long double> x,y;
    sad::Expression<numT> x,y;
    sad::Expression z=x;

    std::map at=sad::at(std::vector{x,y},std::vector{numT(2,1),numT(3.1,0.2)}) ;

    z=y/x+z+numT(1);
    z=z+x;
    z=z*y;
    z=sad::sin(z/y);
    z=sad::exp( z );
    z=sad::atanh( -z*y );

    cout<<evaluate(z, at )<<"\n";
    cout<<evaluate(derivative(z,x), at )<<"\n";
    cout<<evaluate(derivative(z,y), at )<<"\n";
    cout<<evaluate(derivative(z,x,y,x,x), at )<<"\n";
    
    return 0;
}