#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;


template<typename numType>
auto f(const sad::Expression<numType> &x,const sad::Expression<numType> &y){return sad::exp( -(x+y)/(x*y) ) - sad::log(x + numType(1)) * numType(2);}
template<typename numType>
auto g(const sad::Expression<numType> &x,const sad::Expression<numType> &y){return  evaluate(x)>evaluate(y) ? erfc(x)*y : erf(tanh(y)+y*x); };



int main(){
    auto x=sad::Variable<double>();//you can initialize to 0
    x->assign(3.);//you can assign using this (needs that nice syntactic sugar) or sad::assign(x,3.) 

    auto y=sad::Variable(0.1);//you can initialize with a value
    
    auto z=x;//this defines a new Expression 
    z=z*y;//you can redefine it !
    
    /*take all the derivatives*/
    cout<< sad::derivative( f(z,y), {y,x,y,y,x} )<<"\n";
    cout<< sad::derivative( g(x,y), {y,x,x} )<<"\n";
    cout<< sad::derivative( sad::cyl_bessel_k(9.,x) , {x,x,x} )<<"\n";
    cout<< sad::derivative( sad::log(2.,x) , {x,x,x} )<<"\n";

    /*This is the definition of abs. We can "define" the derivative at 0 to be 0*/
    auto t=sad::Zero<double>;
    cout<< sad::abs(t) <<"\n";
    cout<< derivative(sad::abs(t),t)<<"\n";
    cout<< derivative(sad::abs(t+1e-323),t)<<"\n";
    cout<< derivative(sad::abs(t-1e-323),t)<<"\n";

    /*Careful: sad::Variable creates a new VariableType pointer. This means that that the variable changes location, and so the derivatives wrt this variable vanish*/
    z=x;
    cout<<derivative(z,x)<<"\n";
    x=sad::Variable(2.);
    cout<<derivative(z,x)<<"\n";

    /*You really want to use assign for changing the value*/
    z=x;
    cout<<derivative(z,x)<<"\n";
    sad::assign(x,2.);
    cout<<derivative(z,x)<<"\n";


    /*This is cool. The expression is calculated when needed, not when created*/
    sad::assign(x,1.);
    z=sad::One<double>;

    cout<<"running loop...";
    for(std::size_t i=0; i<50000; ++i){z=z*x;}
    cout<<"finished\n";

    cout<<"result:\t";
    cout<<z<<"\n";

    cout<<"derivative:\t";
    cout<<z->der(x)<<"\n";



    return 0;
}