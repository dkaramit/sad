#include<iostream>
#include<SAD/sad.hpp>

using std::cout;

using LD = double;

int main(){
    
    auto x = sad::variable<LD>(10);          
    auto y = sad::variable<LD>(1);          
    sad::Expression<LD> w=y+x;          

    cout<<w<<"\n";
    cout<<derivative(w,x)<<"\n";

    /*this can easily confuse the user. So it introduces room for errors.*/
    y=3*y;
    cout<<w<<"\n";
    cout<<derivative(w,y)<<"\n";


    return 0;
}