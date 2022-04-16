#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;



using LD=double;

auto f(sad::Expression<LD> x,sad::Expression<LD> y){return sad::exp(-x*x*y-y) / x - sad::pow(sad::log(x),y) +sad::sin(x);}

int main(){
    //this is how you define a variable. 
    // It creates a shared pointer Expression<numType>(new VariableType<numType>(1.2)), 
    // where  VariableType is the "true" type of the Variables. But I chose this, in order for everything to be a pointer.
    auto x=sad::Variable<LD>(1.2);
    auto y=sad::Variable<LD>(3.14159);

    // this is one way to define an expression.
    // this is equivalent to std::shared_ptr<ExpressionType<numType>> expr();
    // However, this looks better in my opinion.
    auto expr=sad::Expression<LD>();
    // You could have defined it as Variable, or via expr = x (or any other way; eg decltype(x+x) expr; ). It doesn't matter.
    
    
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

    /*You can't do this in sadET either (the two branches have different type)*/
    auto g = [&](sad::Expression<LD> x,sad::Expression<LD> y){return  sad::evaluate(x)>sad::evaluate(y) ? x*x / y: -y*x;};
    cout<<sad::derivative(g(x,y),{x,y})<<"\n";
    
    x = sad::Variable<LD>(3.14159) ;
    y = sad::Variable<LD>(1.3) ;
    cout<<sad::derivative(g(x,y),{x,y})<<"\n";


    return 0;
}