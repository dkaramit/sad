# sadCpp

Simple Automatic Differentiation (in ```C++```)

![](https://img.shields.io/badge/language-C++-black.svg)  ![](https://tokei.rs/b1/github/dkaramit/sadCpp)
  
![](https://img.shields.io/github/repo-size/dkaramit/sadCpp?color=blue)

## Expressions and Variables

There are two objects that the user needs to know; epxressions and variables. More specifically, both are instances of the class `template<typename numType> sad::Expression`. However, they behave differently depending on how they were initialized.

A variable is an instance of the `Expression` class with respect to which we can differentiate.  Variables are *only* initialized using a number. For example, in
```C++
sad::Expression x =3.; 
```
`x` is a variable.

Expressions are instances of the `Expression` class composed of variables and operations. For example, in 
```C++
sad::Expression x =3.; 
sad::Expression y =2.4; 

sad::Expression f=x+y;
```
`x` and `y` are variables, and `f` is an expression.

### Assignment
We can assign expressions to other expressions, and variables to numbers. If we try to assign a number to an expression we will get the runtime error: "You cannot assign number to Expression!". If we assign an expression to a variable, then only the its value will be copied to the variable. Example:
```C++
sad::Expression x =3.; 
sad::Expression y =2.4; 
sad::Expression f=x+y;

//f=3; //runtime error

f=f*x; //fine. f becomes (x+y)*x
x=5; //fine. x changes to 5.
```
One thing we need to keep in mind is that if a variable changes its value, any expression that depends on it will also change their values and derivatives.

## `evaluate` and `derivative`
There are two functions that the user needs to know; `template<typename numType> sad::evaluate`and `template<typename numType> sad::derivative`.

The first, `sad::evaluate` takes an instance of the `Expression` class and returns its value. 

The `sad::evaluate` function takes at least two instances of the `Expression` class and returns a new expression which is the derivative of the first with respect to the others. Foe example,

```C++
sad::Expression x =3.; 
sad::Expression y =2.4; 
sad::Expression f=x+y;

evaluate(f);//returns the value of x+y

derivative(f,x);// returns \partialf/\partialx 
derivative(f,x,y);// returns \partial^2f/\partialx \partialy 
derivative(f,x,y,y);// returns \partial^3f/\partialx \partialy \partialy 
```

If we differentiate with respect to an expression, we get an expression that has the value of $0$. That is, in the previous example, `derivative(f,f);` returns an instance of `Expression` with the value $0$. 

## Important
1. Once an instance of the `Expression` class is initialized, it cannot change its behavior; en expression remains an expression and a variable a variable. This limits the freedom the user has, which reduces the probability for misuse. 
1. Operations only work for `Expressions` of the same numeric type; expressions that have the same template argument. 

## To-do:
- [ ] Implement as many functions as possible.
- [ ] Code generation for faster execution.
- [ ] Documentation.
- [ ] Allow operations between expressions of different numeric types.

