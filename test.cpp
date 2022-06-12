#include<iostream>
#include<sad.hpp>

using std::cout;

using LD = double;

int main(){

    sad::Expression<LD> x;
    sad::Expression<LD> y;
    sad::Expression<LD> z=x+y;

    std::map<sad::IDType,LD> at=sad::at<LD>({x,y},{6,2}) ;
    
    cout<<x.evaluate( at )<<"\n";
    cout<<x.derivative(1).evaluate( at )<<"\n";
    cout<<x.derivative(2).evaluate( at )<<"\n";

    cout<<z.evaluate( at )<<"\n";
    cout<<z.derivative(1).evaluate( at )<<"\n";
    cout<<z.derivative(2).evaluate( at )<<"\n";

    cout<<(z*x).evaluate( at )<<"\n";
    cout<<(z*x).derivative(1).evaluate( at )<<"\n";
    cout<<(z*x).derivative(2).evaluate( at )<<"\n";


    return 0;
}