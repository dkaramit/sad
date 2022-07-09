#ifndef MISC_H
#define MISC_H

#include <iostream>
#include<memory>
#include<map>
#include<vector>
#include<string>

#define PPF std::cout<<__PRETTY_FUNCTION__<<"\n"

namespace sad{
using std::map;
using std::vector;
using std::string;
using std::to_string;

using IDType=unsigned int;


/*declaration of classes*/
template<typename numType> class AbstractExpression;
template<typename numType> class Variable;
template<typename numType> class Expression;

/*Alias for shared pointer to AbstractExpression*/
template<typename numType> using AbsExp_ptr=std::shared_ptr<AbstractExpression<numType>>; 



/*----these constants will be helpful---*/
template<typename numType>static const auto ONE     = Expression<numType>::constant(1);
template<typename numType>static const auto TWO     = Expression<numType>::constant(2);
template<typename numType>static const auto ZERO    = Expression<numType>::constant(0);
template<typename numType>static const auto NEG_ONE = Expression<numType>::constant(-1);
template<typename numType>static const auto HALF    = Expression<numType>::constant(0.5);
template<typename numType>static const auto PI      = Expression<numType>::constant(M_PI);
template<typename numType>static const auto PI2     = Expression<numType>::constant(M_PI*M_PI);
template<typename numType>static const auto SQRT_PI = Expression<numType>::constant(2/M_2_SQRTPI);

//you can use this to evaluate constants!
template<typename numType>static const map<IDType,numType> empty_at;

template<typename numType> auto print_expr(const Expression<numType> &expr){return expr.str();}
template<typename numType> auto print_expr(const numType &x){return to_string(x);}





template<typename T> char const* pf() { return __PRETTY_FUNCTION__; }
template<typename T> string get_type_name() {
    auto str = string(pf<T>());
    auto pos1 = str.find("= ");
    auto pos2 = str.find("]");
    return str.substr(pos1+2,pos2-(pos1+2)); 
}

template<typename numType> auto functions_generation(const vector<Expression<numType>>& Variables, const vector<Expression<numType>>& Expressions){
    string type =  get_type_name<numType>();
    
    size_t NVar=Variables.size();

    string var_list=type+" ";
    for(size_t i=0; i<NVar; ++i){var_list+= print_expr(Variables[i]) + (i==NVar-1 ? "" : ", "+type+" ") ;}

    string cls="";

    // for(auto var:Variables){cls+= type+string(" ")+print_expr(var)+";\n" ;}
    // cls+="\n";

    size_t func_id=0;
    for(auto expr:Expressions){
        cls+= type+" func_"+to_string(++func_id)+"("+var_list+"){ return "+print_expr(expr)+"; }\n" ;
    }
    
    return cls;
}

template<typename numType> auto class_generation(const string& class_name, const vector<Expression<numType>>& Variables, const vector<Expression<numType>>& Expressions){
    string type =  get_type_name<numType>();
    
    size_t NVar=Variables.size();


    string cls="class "+class_name+"{\n\t";

    cls+="\n\tpublic:\n\t";
    size_t func_id=0;
    for(auto expr:Expressions){
        cls+= type+" func_"+to_string(++func_id)+"(){ return "+print_expr(expr)+"; }\n\t" ;
    }
    

    cls+="\n\t";
    for(size_t i=0; i<NVar; ++i){cls+= print_expr(Variables[i]) + (i==NVar-1 ? ";" : ", ") ;}
    cls+="\n};";
    
    return cls;
}


}



#endif