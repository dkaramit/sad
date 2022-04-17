#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;


template<typename LT,typename RT>
auto f(const sad::Expression<LT> &x,const sad::Expression<RT> &y){return sad::exp(-x*x*y-y) / x - sad::pow(sad::log(x),y) +sad::sin(x);}
template<typename LT,typename RT>
auto g(const sad::Expression<LT> &x,const sad::Expression<RT> &y){return  evaluate(x)>evaluate(y) ? erfc(x)*y : erf(tanh(y)+y*x); };



int main(){
    auto x=sad::Variable(3.);
    auto y=sad::Variable(0.1);
    cout<< sad::derivative( g(x,y), {y,x,x} )<<"\n";
    cout<< sad::derivative( f(x,y), {y,x,y,y,x} )<<"\n";
    cout<< sad::derivative( sad::cyl_bessel_k(1,x) , {x,x,x} )<<"\n";
    cout<< sad::derivative( (x^2.) , {x} )<<"\n";
    cout<< sad::derivative( 1.+x/3. , {x} )<<"\n";

    return 0;
}