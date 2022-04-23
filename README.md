# sadCpp

Simple Automatic Differentiation (in ```C++```)

![](https://img.shields.io/badge/language-C++-black.svg)  ![](https://tokei.rs/b1/github/dkaramit/sadCpp)
  
![](https://img.shields.io/github/repo-size/dkaramit/sadCpp?color=blue)

## Basic structure
The basic objects in `sadCpp` are expressions; instances of the `sad::Expression<numType>` class (`numType` is the numerical type we wish to use; e.g. `double`). They can be initiated in two different ways; as a variable or as a general expression:

1. definition using a numeric value `sad::Expression x=5.;` or `sad::Expression x(5.);` means that `x` ***is*** a variable; something with respect to which you can differentiate. 

2. definition using an expression `sad::Expression y=x;` or  `sad::Expression y=x+x;` (or any other expression) means that `y` ***is not*** a variable; all the derivatives with respect to `y` are zero.

Note that the default constructor of the `Expression` class is deleted, because we should always know whether an instance is a variable or not. The reason for this, is to allow an expression to change its state to a variable and vice versa. Consider the following:

```c++
sad::Expression x=5.;           //variable
sad::Expression y=x*x+x;        //expression

y=12.;                          //variable
y=y;                            //expression

y=y+x;                          //expression
y=x;                            //expression
```

The rule here is: ***If something is assigned a numerical value, it is a variable. Otherwise, it is an expression.***


## `evaluate` and `derivative`. 
Appart from the various mathematical functions, the two functions in the heart of `sadCpp` are `sad::Expression::evaluate` and `sad::Expression::derivative`. The first, returns the value of an instance of the `Expression` class. The second is applied to takes an instance of `sad::Expression` and takes as argument an instance of `sad::Expression`, and returns the derivative of the first with respect to the second.


For example:
```c++
sad::Expression x=5.;          
sad::Expression y=1.;
sad::Expression f=x*x+y*y;

cout<< f.evaluate() << "\n";                    //prints 26

cout<< f.derivative(x) << "\n";                 //prints 10
cout<< f.derivative(y) << "\n";                 //prints 2

cout<< f.derivative(x).derivative(x) << "\n";   //prints 2
cout<< f.derivative(x).derivative(y) << "\n";   //prints 0
cout<< f.derivative(y).derivative(x) << "\n";   //prints 0
cout<< f.derivative(y).derivative(y) << "\n";   //prints 2
```




## A bit more technical stuff
The `Expression class` is just a friend to all other classes. It is the glue that holds all other classes together. Under the hood it is allows its instances to hold a pointer to the abstract (base) class, `sad::AbstractExpression<numType>`.

For this clas all the other are derived. For example the class `sad::Variable<numType>` is derived from `sad::AbstractExpression<numType>`. and defines how variables are declared, what are their values and derivatives. The `sad::Addition<numType>` class defines how the addition is evaluated, and what is the rule for the derivative of two instances of the `Expression` class are added (i.e. it defines what kind is the addition). All other basic operations (multiplication, division, sin, cos, exp, log ...) are similar classes, all derived from the  `AbstractExpression` class.

This means that the value of the expression chnages if the values of its variables change.

For example, the code below prints 9 and then 64, because y is assinge to the expression x*x, which changes value if the value of x changes:
```c++
sad::Expression<double> x(3);
sad::Expression<double> y(0);

y=x*x;
cout<< y <<"\n";
x=8;
cout<< y <<"\n";

```

However, the following code prints 9 and 9, since y is assunged to the value of x*x before x is assigned the value 8.
```c++
sad::Expression<double> x(3);
sad::Expression<double> y(0);

y=(x*x).evaluate();
cout<< y <<"\n";
x=8;
cout<< y <<"\n";

```

## What is a variable?
The definition used in `sadCpp` is the one brifely hinted earlier; ***variable is an instance of the `Expression` class with respect to which one can differentiate and it holds its numerical value***. In contrast to this, an expression is just a "collection" of operations on varibles. This means that 1)we cannot differentiate wrt an expression (this operation *always* returns zero) and 2) an expressions does not hold its value; it is evaluated at the point that is needed.

## How is `Expression` implemented?
The `Expression` class has a number of members that just call the corresponding members of the `AbstractExpression` pointer; `eveluate` and `derivative`. Every other class has this one as a friend in order for it to have access to the private members of all other classes.

It also has three constructors and two assignment operators. The user only interacts with the two contractors sown in the example above (`Expression(const Expression &)` and `Expression(const numType &)`), with the third one being the one used by the different opetors that return an new  `AbstractExpression` pointer that cooresponds to their specific operation. For example `operator+` takes two expressions and returns a new instance of `Expression` via an `AbstractExpression`  pointer that is assigned to an instance of the `Addition` class. 

The two assignment operators, `Expression* operator=(const numType &)` and `Expression* operator=(const Expression &)`, are used to assign a number to an expression (turning it to a variable) or assign another expression (making it an expression).

## How the derivatives are taken?
The derivatives of all operators return expressions that have derivatives of its subexpressions (for example the derivative of the addition returns the addition of the derivatives of left- and right-hand side), until a variable returns 0 or 1 (instances of `Expression` that hold these values). This means that we need to identify with respect to which variable we differentiate, so that the correct value is returned. 

For the identification, `sadCpp` uses the address of the  `AbstractExpression` pointer of the expression at hand. That is, when we ask for the derivative of a variable wrt another, we get 1 if the correspond to the same `AbstractExpression`, and 0 otherwise.

## How does an instance know that it is a variable.
Simple. `sad::Expression` has a `bool` private member called `is_var`. This becomes `true` when the instance is assigned a numerical value, and `false` when it is assigned another expression. The main use of this variable is to in the `sad::Expression::evaluate` method. Each instance needs to know if it has a value or not, because it needs to know if the `AbstractExpression` pointer has a value or not. The reason is that only members of the `sad::Variable` class have a member called `value`. So, if one casts this `AbstractExpression` pointer to a pointer to an expression and asks for the member value, the result will probably be a segfault. There are other ways of doing this, for example every expression could holds its value, but this would not allow the expressions to change by changing the variables that constitutes them. So, it is the `sadCpp` design choice to just use a `bool` in order to keep track of what is a variable or not. 



## To-do:
- [ ] Implement as many functions as possible.
- [ ] Output to ![sadET](https://github.com/dkaramit/sadET). This will be useful because `sadET` is faster, since it uses expression templates.
- [ ] Documentation.

