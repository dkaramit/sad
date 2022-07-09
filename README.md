# sadCpp

Simple Automatic Differentiation (in ```C++```)

![](https://img.shields.io/badge/language-C++-black.svg)  ![](https://tokei.rs/b1/github/dkaramit/sadCpp)
  
![](https://img.shields.io/github/repo-size/dkaramit/sadCpp?color=blue)

## Expressions and Variables

There is one basic class: `sad::Expression<numType>`. The way instances are declared determine their function. Declaring an instance as
```C++
sad::Expression<double> x; 
```
declares a variable that, when evaluated (see later), returns a double. We should note that the default templte argument is ```double```, so it may be omitted. Then, type-deduction allows us to skip *all* other template arguments.

Declaring an instance as
```C++
sad::Expression<double> c=2; 
```
declares a constant that, holds the value `(double)2`. Note that you can skip the template parameter here! 


Declaring an instance through another Expression
```C++
sad::Expression<double> f=x+c; 
```
declares a general expression. 

This library is all about manipulating such expressions!

### Assignment
We can assign expressions to other expressions. Example:
```C++
sad::Expression<double> x; 
sad::Expression<double> y; 
sad::Expression f=x+y;

f=f*x; //fine. f becomes (x+y)*x
```

## `evaluate` and `derivative`
There are two functions that the user needs to know; `template<typename numType> sad::evaluate`and `template<typename numType> sad::derivative`.

The first, `sad::evaluate` takes an instance of the `Expression`, and a `std::map<unsigned int, numType>` class and returns its value setting the variables at the values described in the map.  

The `sad::derivative` function takes at least two instances of the `Expression` class and returns a new expression which is the derivative of the first with respect to the others. For example,

```C++
sad::Expression<double> x,y; 
sad::Expression f=x+y;

std::map at=sad::at(std::vector{x,y},std::vector{6,2}) ;

evaluate(f,at);//returns the value of x+y

derivative(f,x);// returns \partialf/\partialx 
derivative(f,x,y);// returns \partial^2f/\partialx \partialy 
derivative(f,x,y,y);// returns \partial^3f/\partialx \partialy \partialy 
```

If we differentiate with respect to an expression, we get an expression that has the value of $0$. That is, in the previous example, `derivative(f,f);` returns an instance of `Expression` with the value `0`. 

Note: you only need to explicitely use a template parameter for variables. All other instances can deduct the type since `c++17`.

## Code generation
There are two function that can print expressions as functions or classes.

## To-do:
- [ ] Implement as many functions as possible.
- [ ] Code generation for faster execution.

