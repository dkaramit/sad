#include<iostream>
#include<SAD/sad.hpp>

using std::cout;

using LD = double;

int main(){
    
    auto x = sad::Expression<LD>::variable(10);          
    auto y = sad::Expression<LD>::variable(2.8); 

    sad::Expression z=x;     
    // z=5; //Forbidden!!

    z=z*y*x;

    cout<<z<<"\n";   
    cout<<derivative(z,x)<<"\n";   
    cout<<derivative(z,y)<<"\n";   

    x=z;//copies the value of z
    cout<<z<<"\n";   
    cout<<derivative(z,x)<<"\n";   
    cout<<derivative(z,y)<<"\n";   


    return 0;
}