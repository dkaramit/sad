#include<iostream>
#include<vector>
#include<cmath>
#include<sad.hpp>

using std::cout;
using std::vector;

int main(){

    sad::Expression x,y;
    sad::Expression z=log(x);

    std::map at=sad::at(std::vector{x,y},std::vector{0.325,3.}) ;


    cout<<z.subExpr().evaluate(at)<<"\n";


    return 0;
}