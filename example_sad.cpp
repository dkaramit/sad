// Example on how to generate expressions and types for sadET

#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;



using LD=double;

auto f(sad::Expression<LD> x,sad::Expression<LD> y){return sad::exp(-x*x*y-y) / x - sad::pow(sad::log(x),y) +sad::sin(x);}

int main(){
    auto x=sad::Variable<LD>(1.2);

    auto y=sad::Variable<LD>(3.14159);
    auto expr=sad::Expression<LD>();
    
    
    cout<<x<<"\n";
    x = sad::Variable<LD>(1.3) ;
    cout<<sad::evaluate(x)<<"\n";
    
    

    expr = x*x*y + x-y/x;
    cout<<sad::derivative(expr,{x,x,y})<<"\n";
    cout<<sad::derivative(-expr,{x,y,x})<<"\n";

    cout<<sad::derivative(f(x,y),x)<<"\n";
    cout<<sad::derivative(f(x,y),y)<<"\n";
    cout<<sad::derivative(f(x,y),{x,y})<<"\n";
    cout<<sad::derivative(f(x,y),{y,x})<<"\n";


    cout<<sad::derivative( sad::pow(f(x,y),sad::Variable<LD>(10)) ,{y,x,x,x,x})<<"\n";
    /*in contrast to sadET, you can do this:*/
    expr = sad::Variable<LD>(1);
    for(size_t i=0; i<10; ++i){expr=expr*f(x,y);}
    cout<<sad::derivative(expr,{y,x,x,x,x})<<"\n";



    return 0;
}