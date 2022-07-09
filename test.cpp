#include<iostream>
#include<vector>
#include<cmath>
#include<sad.hpp>

using std::cout;
using std::vector;

int main(){

    sad::Expression x,y;
    sad::Expression z=sin(x);
    sad::Expression f;

    std::map at=sad::at(vector{x},vector{0.}) ;

    for(int i=0; i<100; ++i){z=tanh(z/y+x);}
    
    f=derivative(z,x);

    cout<<print_expr(z)<<"\n";
    cout<<print_expr(f)<<"\n";


    return 0;
}