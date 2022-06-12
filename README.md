# sadCpp

Simple Automatic Differentiation (in ```C++```)

![](https://img.shields.io/badge/language-C++-black.svg)  ![](https://tokei.rs/b1/github/dkaramit/sadCpp)
  
![](https://img.shields.io/github/repo-size/dkaramit/sadCpp?color=blue)

## Expressions and Variables

There are two objects that the user needs to know; epxressions and variables. More specifically, both are instances of the class `template<typename numType> sad::Expression`. However, they behave differently depending on how they were initialized.

A variable is an instance of the `Expression` class with respect to which we can differentiate.  Variables are *only* initialized by the default constructor. For example, in
```C++
sad::Expression x; 
```
`x` is a variable.

Expressions are instances of the `Expression` class composed of variables and operations. For example, in 
```C++
sad::Expression x; 
sad::Expression y; 

sad::Expression f=x+y;
```
`x` and `y` are variables, and `f` is an expression.

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

The `sad::derivative` function takes at least two instances of the `Expression` class and returns a new expression which is the derivative of the first with respect to the others. FoR example,

```C++
sad::Expression x; 
sad::Expression y; 
sad::Expression f=x+y;

std::map at=sad::at<LD>({x,y},{6,2}) ;

evaluate(f,at);//returns the value of x+y

derivative(f,x);// returns \partialf/\partialx 
derivative(f,x,y);// returns \partial^2f/\partialx \partialy 
derivative(f,x,y,y);// returns \partial^3f/\partialx \partialy \partialy 
```

If we differentiate with respect to an expression, we get an expression that has the value of $0$. That is, in the previous example, `derivative(f,f);` returns an instance of `Expression` with the value $0$. 


## To-do:
- [ ] IMPORTANT: Allow different types by playing with `numType`.
- [ ] Implement as many functions as possible.
- [ ] Code generation for faster execution.
- [ ] Documentation.
- [ ] Allow operations between expressions of different numeric types.

