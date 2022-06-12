#include<iostream>
#include<sad.hpp>

using std::cout;

using LD = double;

int main(){

    sad::Expression<LD> x;
    sad::Expression<LD> y;
    sad::Expression<LD> z=x+y*x;

    std::map at=sad::at<LD>({x,y},{6,2}) ;
    
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