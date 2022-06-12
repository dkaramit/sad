#include<iostream>
#include<sad.hpp>

using std::cout;

using LD = double;

int main(){
    
    auto x = sad::Expression<LD>::variable(10);          
    sad::Expression y = 2.8; 

    sad::Expression z=x;     
    // z=5; //runtime error!

    z=z+y;

    cout<<z<<"\n";   
    cout<<derivative(z,x)<<"\n";   
    cout<<derivative(z,y)<<"\n";   

    x=z;//copies the value of z
    cout<<z<<"\n";   
    cout<<derivative(z,x)<<"\n";   
    cout<<derivative(z,y)<<"\n";   

    return 0;
}