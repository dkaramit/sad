#include<iostream>
#include<SAD/sad.hpp>

using std::cout;

using LD = double;

int main(){
    sad::Expression<LD> x(10);          
    sad::Expression<LD> y(1);          
    auto z = 1+x+1.f*y+2*y*y*3;
    z=z*2+x;
    
    return 0;
}