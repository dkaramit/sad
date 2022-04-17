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
    auto x=sad::Variable(3.);
    auto y=sad::Variable(0.1);
    auto z=x;
    z=z*y;
    cout<< sad::derivative( f(z,y), {y,x,y,y,x} )<<"\n";
    cout<< sad::derivative( g(x,y), {y,x,x} )<<"\n";
    cout<< sad::derivative( sad::cyl_bessel_k(1,x) , {x,x,x} )<<"\n";
    cout<< sad::derivative( sad::log(2.,x) , {x,x,x} )<<"\n";

    return 0;
}