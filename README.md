# sadCpp

Simple Automatic Differentiation (in ```C++```)

![](https://img.shields.io/badge/language-C++-black.svg)  ![](https://tokei.rs/b1/github/dkaramit/sadCpp)
  
![](https://img.shields.io/github/repo-size/dkaramit/sadCpp?color=blue)


## Example

In order to use it, you just include this ```#include<SAD/sad.hpp>``` in your code. Then, you have access to all classes and functions
under the ```sad``` nmaespace. As an example, consider the function

$$
f(x,y) = e^{x/y} - \sin(\tan(\log(y+1)))
$$

This can be simply implemented as 

```
template<typename numType>
auto f(sad::Expression<numType> x, sad::Expression<numType> y){
    return sad::exp(x/y)- sad::sin(sad::tan(sad::log(y+ numType(1) ))); // we need to write numType(1) instead of 1, because all numeric types have to match.
}
```

Notice here that we pass to the function ```sad::Expression```. More on that later.


Then, in the main program, we can do can calculate the vale as well as derivatives of this function:
```
auto x=sad::Variable<double>();//you can initialize to 0
auto y=sad::Variable(1.);//you can initialize to a value (with type deduction this is prettier)

std::cout << f(x,y) << "\n"; // prints the value
std::cout << derivative(f(x,y),x) << "\n"; // prints the derivative wrt x (at the value of x)
std::cout << derivative(f(x,y),{x,x,y}) << "\n"; // prints \dfrac{\partial^3 f(x,y)}{\partial x \partial x \partial y} 
```

You can change the variable using ```x=sad::Variable(5.)```. This changes both the value and the variable itself. This means that
```
auto x=sad::Variable(2.);
auto p=x*x;

std::cout << derivative(p,x) << "\n"; // prints 4

x=sad::Variable(2.);
std::cout << derivative(p,x) << "\n"; // prints 0
```

If you just want to assign new value, you can use ```sad::asign```

```
auto x=sad::Variable(2.);
auto p=x*x;

std::cout << derivative(p,x) << "\n"; // prints 4

sad::assign(x,1.);
std::cout << derivative(p,x) << "\n"; // prints 2
```

## What is ```sad::Expression```?

Everything is an Expression; even the variables. To be more precise, there are two basic classes; the base one ```template<typename numType> ExpressionType``` and ```template<typename numType> VariableType```. The first one is a base abstruct class, while the other is derived. On the other hand ```sad::Expression``` is an alias for a shared pointer to ExpressionType. This srtucture allows us to define all operators, functions, variables as  pointers to ExpressionType, and use the overriden member functions to define the derivatives. For example the ```VariableType``` class has overrides the ```der``` member as

```
template<typename numType>
sad::Expression<numType> sad::VariableType<numType>::der(const sad::Expression<numType> &wrt) const {
        if(wrt.get()==this){return sad::One<numType>;}
        return sad::Zero<numType>;
}
```

Here ```sad::One``` and ```sad::Zero``` are pointers to ```VariablesType``` that hold the values 1 and 0, respectively.

## What is ```sad::Variable```?
This is just a function that returns shared pointer to a new ```VariableType```, which of course ```Expression```. This is the reason that reassinging a varialbe using ```=sad::Variable``` changes the derivatives as well.  

## ```sad::evaluate```, ```sad::derivative```, and ```sad::assign```

There are three functions that we need to know, in order to manipulate expressions. The first, ```sad::evaluate``` takes a ```sad::Expression``` and returns its value. 

The second takes two ```sad::Expression``` and returns the derivative of the first with respect to the second. It is implied here that the second is something created using ```sad::Variable```. It is possible to make it so that you can take derivatives of expression wrt other expressions (e.g $\dfrac{d f(x,y) }{d(x+y)}$ ), but in order for this to work correctly one needs to symbolically manipulate the expression; i.e. it completely changes the purpose of automatic differentiation.   If you pass a ```std::valarray``` of ```sad::Expression``` as a second argument to ```sad::derivative```, you get the derivative wrt all the varialbes in the list.

Finally, ```sad::assign``` is used to change the numerical value of an instance created using ```sad::Variable``` (as in the example above). If you pass any other type of ```sad::Expression```, nothing will happen. However, if you pass a variable that is assigned to another variable, both their values will change, since we are manipulating pointers.   

## To-do:
- [ ] Implement as many functions as possible.
- [ ] Output to ![sadET](https://github.com/dkaramit/sadET). This will be useful since sadET uses expression templates.
- [ ] Documentation.

