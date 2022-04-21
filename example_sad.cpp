#include<iostream>
#include<memory>
#include<vector>
#include<SAD/sad.hpp>

using std::cout;
using std::vector;


int main(){
  sad::Expression<double> x(3);
  sad::Expression<double> y(33);
	cout<<x.eval()<<"\n";
	cout<<x.der(x).eval()<<"\n";
	
	cout<<(x+y).der(x).eval()<<"\n";
	


  return 0;
}