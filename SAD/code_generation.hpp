#ifndef codeGen_H
#define codeGen_H

#include <iostream>
#include<memory>
#include<map>
#include<vector>
#include<string>


namespace sad{

template<typename T> char const* pf() { return __PRETTY_FUNCTION__; }
template<typename T> string get_type_name() {
    auto str = string(pf<T>());
    auto pos1 = str.find("= ");
    auto pos2 = str.find("]");
    return str.substr(pos1+2,pos2-(pos1+2)); 
}

template<typename numType> auto functions_generation(const vector<Expression<numType>>& Variables, const vector<Expression<numType>>& Expressions){
    string type = "numType";

    map<IDType,Expression<numType>> uniqueV;
    for(auto V:Variables){ if(V.ID()!=0){uniqueV[V.ID()]=V;} }
    size_t NVar=uniqueV.size();


    string var_list="const "+type+"& ";
    size_t i =0;
    for(auto &el : uniqueV ){ var_list+= print_expr(el.second) + (i++==NVar-1 ? "" : ", const "+type+"& ");}

    string fn="";

    size_t func_id=0;
    for(auto expr:Expressions){
        fn+= "template<typename numType> "+type+" func_"+to_string(++func_id)+"("+var_list+"){ return "+print_expr(expr)+"; }\n" ;
    }
    
    return fn;
}

template<typename numType> auto class_generation(const string& class_name, const vector<Expression<numType>>& Variables, const vector<Expression<numType>>& Expressions){
    string type =  "numType";

    map<IDType,Expression<numType>> uniqueV;
    for(auto V:Variables){ if(V.ID()!=0){uniqueV[V.ID()]=V;} }
    size_t NVar=uniqueV.size();

    


    string cls="template<typename numType>\nclass "+class_name+"{\n\t";
    cls+="~"+class_name+"()=default;\n\t";
    cls+=class_name+"()=default;\n\t";

    cls+="\n\tpublic:\n\t";
    size_t func_id=0;
    for(auto expr:Expressions){
        cls+= type+" func_"+to_string(++func_id)+"(){ return "+print_expr(expr)+"; }\n\t" ;
    }
    

    cls+="\n\t"+type+" ";

    size_t i =0;
    for(auto &el : uniqueV ){ cls+= print_expr(el.second) + (i++==NVar-1 ? ";" : ", ");}
    
    cls+="\n};";
    
    return cls;
}


}



#endif