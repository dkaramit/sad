#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;


int main(){
  sad::Expression<double> x(3);
  sad::Expression<double> y(33);
  
	cout<<(y+x).der(x).eval()<<"\n";
	cout<<(y+x).der(y).eval()<<"\n";
  auto p=x;//this is good.
	cout<<(y+p+x).der(p).eval()<<"\n";

	  
  sad::Expression<double> z(33);//no name (or empty charachter) implies a constant (the derivative wrt itself is zero)
	cout<<z.der(x).eval()<<"\n";
  
  
  
  
  return 0;
}