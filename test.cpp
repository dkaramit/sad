#include<iostream>
#include<vector>
#include<cmath>
#include<sad.hpp>

using std::cout;
using std::vector;

int main(){

    sad::Expression x,y;
    sad::Expression z=log(x);


    cout<<z.head()<<"\n";



    return 0;
}