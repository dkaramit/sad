#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;


int main(){
    /*This is how you define new variables*/
    sad::Expression<double> x(3);
    sad::Expression<double> y(10);


    /*This is how you define new expressions*/
    sad::Expression<double> expr=(y+x)*x*y;
    /*You can simply reassign with no problem*/
    expr=expr+x*y;

    /*<< is overloaded*/
    cout<<(expr)<<"\n";
    /*But you can evaluate the result as*/
    cout<<sad::evaluate(expr) + 4.<<"\n";
    
    /*take all the derivatives*/
    cout<<sad::derivative(expr,x)<<"\n";
    cout<<sad::derivative(expr,y)<<"\n";
    
    cout<<sad::derivative(expr,{x,x})<<"\n";
    cout<<sad::derivative(expr,{x,y})<<"\n";
    cout<<sad::derivative(expr,{y,x})<<"\n";
    cout<<sad::derivative(expr,{y,y})<<"\n";

    cout<<sad::derivative(expr,{y,y,x})<<"\n";
    cout<<sad::derivative(expr,{y,x,x})<<"\n";
    cout<<sad::derivative(expr,{y,y,y})<<"\n";
    cout<<sad::derivative(expr,{x,x,x})<<"\n";

    /*you can reassign variables, and still take the derivatives with no issue*/
    x=12.;
    cout<<expr<<"\n";
    cout<<sad::derivative(expr,x)<<"\n";

    /*This is allowed, but the value of an expression does not change, since it depends on its variables*/
    // I am not sure how good of a design this is, but let's see..
    expr=8;
    cout<<expr<<"\n";

return 0;
}