/*If you can, try to declare a variable that holds the expression and then evaluate it at some numerical points.*/

#include<iostream>
#include<chrono>
#include<sad.hpp>

using std::cout;
using std::cerr;

class Timer{
    public:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> finish;
    std::chrono::duration<double> dt;
    Timer(){
        start = std::chrono::high_resolution_clock::now();
    };
    ~Timer(){
        finish = std::chrono::high_resolution_clock::now();
        dt = finish - start;
        std::cerr<<dt.count()<<"\n";
    };
};


int main(){

    sad::Expression x,y;
    sad::Expression z=x;


    std::map at=sad::at(std::vector{x,y},std::vector{-1.,3.1}) ;
    
    z=1.-z-1./y/x/1. -1. ;
    z=z+x;
    z=z*y;
    z=sad::sin(z/y);
    z=sad::exp(sad::abs( z )*2.);

    {Timer _;    
    cerr<<"Run derivative and evaluate together.\n";
    for(auto i=0;i<100;++i){evaluate(derivative(z,x,y,x,x,y,x), at );}
    }
    
    {Timer _;    
    cerr<<"Run derivative once and evaluate after.\n";
    sad::Expression f = derivative(z,x,y,x,x,y,x);
    for(auto i=0;i<100;++i){evaluate(f, at );}
    }

    return 0;
}