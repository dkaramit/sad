#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;


int main(){
    sad::Expression<double> x(3);
    sad::Expression<double> y(10);

    cout<<((y+x)*x*y)<<"\n";

    cout<<sad::derivative((y+x)*x*y,x)<<"\n";
    cout<<sad::derivative((y+x)*x*y,y)<<"\n";
    
    cout<<sad::derivative((y+x)*x*y,{x,x})<<"\n";
    cout<<sad::derivative((y+x)*x*y,{x,y})<<"\n";
    cout<<sad::derivative((y+x)*x*y,{y,x})<<"\n";
    cout<<sad::derivative((y+x)*x*y,{y,y})<<"\n";

    cout<<sad::derivative((y+x)*x*y,{y,y,x})<<"\n";
    cout<<sad::derivative((y+x)*x*y,{y,x,x})<<"\n";
    cout<<sad::derivative((y+x)*x*y,{y,y,y})<<"\n";
    cout<<sad::derivative((y+x)*x*y,{x,x,x})<<"\n";

return 0;
}