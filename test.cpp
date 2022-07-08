#include<iostream>
#include<sad.hpp>

using std::cout;

int main(){

    sad::Expression x,y;
    auto c=sad::Expression<double>::constant(2.);

    std::map at=sad::at(std::vector{x,y},std::vector{0.325,3.}) ;
    
    cout<<sad::str( pow(x,y)  )<<"\n";
    cout<<sad::str( pow(x,1.)  )<<"\n";
    cout<<sad::str( pow(x,0.)  )<<"\n";
    cout<<sad::str( pow(x,c)  )<<"\n";
    cout<<sad::str( exp(log(x))  )<<"\n";

    return 0;
}