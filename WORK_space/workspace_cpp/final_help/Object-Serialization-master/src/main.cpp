#include <string>
#include <iostream>
#include <typeinfo>
#include "include/Binary.h"
#include "include/Reflection.h"
#include "include/Seel.h"
#include "include/Seelxml.h"
#include "include/ToXML.h"


struct User{
    User(){
        id = 3200;
        age = 20;
        gpa = {"good", "second"};
    }
    ~User(){}
    inline bool operator==(const User& rhs){
        if(id == rhs.id)
            if(age == rhs.age)
                if(gpa == rhs.gpa)
                    return true;
        return false;
    }
        int id;
        int age;
        std::vector<std::string> gpa;
        std::map<int,float> sub;
        std::string test_string = "hello world";
        std::vector<int> test_vector = {1,2,3};
        std::list<int> test_list = {4,5,6};
        std::set<int> test_set = {7,8,9};
        std::map<int,std::string> test_map = {{1,"how"},{2,"are"},{3,"you"}};
        std::pair<std::string,std::string> test_pair = {"happy birthday", "to you!"};
        std::vector<std::list<int>> test_v_l = {test_list,{2,6,8,45,6},{898,7787,5454}};
        std::map<std::vector<int>,std::string> test_i_m = {{test_vector,"first is here"},{{7,45,88,954,}, "this is the second"}};
        std::list<std::vector<int>> test_l_v = {{2,6,8,45,6},{898,7787,5454}};
};
DEFINE_STRUCT_SCHEMA(User,
                    DEFINE_STRUCT_FIELD(id,"id"),
                    DEFINE_STRUCT_FIELD(age,"age"),
                    DEFINE_STRUCT_FIELD(gpa,"gpa"),
                    DEFINE_STRUCT_FIELD(sub,"sub"),
                    DEFINE_STRUCT_FIELD(test_string,"test_string"),
                    DEFINE_STRUCT_FIELD(test_vector,"test_vector"),
                    DEFINE_STRUCT_FIELD(test_list,"test_list"),
                    DEFINE_STRUCT_FIELD(test_set,"test_set"),
                    DEFINE_STRUCT_FIELD(test_map,"test_map"),
                    DEFINE_STRUCT_FIELD(test_pair,"test_pair"),
                    DEFINE_STRUCT_FIELD(test_v_l,"test_v_l"),
                    DEFINE_STRUCT_FIELD(test_i_m,"test_i_m"),
                    DEFINE_STRUCT_FIELD(test_l_v,"test_l_v")
                    );

struct Demo{
    Demo(){}
    void Init_r(){
        id = 1;
        ratio = 3.1415926535;
        name = "Pass test!";
        token.clear();
        token.push_back("item[1]");
        token.push_back("item[2]");
        token.push_back("item[3]");
    }
    inline bool operator==(const Demo& rvl){
        if(id==rvl.id)
            if(ratio == rvl.ratio)
                if(name == rvl.name)
                    if(token == rvl.token)
                        return true;
        return false;
    }

    int id;
    float ratio;
    std::string name;
    std::vector<std::string> token;
    User cases;
};
DEFINE_STRUCT_SCHEMA(Demo,
                    DEFINE_STRUCT_FIELD(id,"id"),
                    DEFINE_STRUCT_FIELD(ratio,"ratio"),
                    DEFINE_STRUCT_FIELD(name,"name"),
                    DEFINE_STRUCT_FIELD(token,"token"),
                    DEFINE_STRUCT_FIELD(cases,"cases"));



void test_bin();
void test_xml();


template<typename T>
void test_test_bin(T& src){
    T des;
    binary::serialize(src,"se.bin");
    binary::deserialize(des,"se.bin");
    std::cout << "The test type is " << typeid(T).name() << std::endl;
    std::cout << std::boolalpha << "The result is " << (bool)(src == des) << std::endl;
}
template<typename T>
void test_test_xml(T& src){
    T des;
    xml::serialize(src,"se.xml");
    xml::deserialize(des,"se.xml");
    std::cout << "The test type is " << typeid(T).name() << std::endl;
    std::cout << std::boolalpha << "The result is " << (bool)(src == des) << std::endl;
}





void test_usrdefined(){
    Demo src,des;
    src.Init_r();
    src.cases.age = 99;
    //des.Init_r();
    binary::serialize(src,"se.bin");
    binary::deserialize(des,"se.bin");
    if(src == des){
        std::cout << "struct Demo serialized successfully" << std::endl;
    }
    
    std::cout << std::boolalpha << (src == des) << std::endl; 
}




void test_bin(){
    
    
    bool test_bool = true;
    char test_char = 'a';
    int test_int = 32;
    float test_float = 1.414;
    std::string test_string = "hello world";
    std::vector<int> test_vector = {1,2,3};
    std::list<int> test_list = {4,5,6};
    std::set<int> test_set = {7,8,9};
    std::map<int,std::string> test_map = {{1,"how"},{2,"are"},{3,"you"}};
    std::pair<std::string,std::string> test_pair = {"happy birthday", "to you!"};
    std::vector<std::list<int>> test_v_l = {test_list,{2,6,8,45,6},{898,7787,5454}};
    std::map<std::vector<int>,std::string> test_i_m = {{test_vector,"first is here"},{{7,45,88,954,}, "this is the second"}};
    std::list<std::vector<int>> test_l_v = {{2,6,8,45,6},{898,7787,5454}};
    
    test_test_bin(test_bool);
    test_test_bin(test_char);
    test_test_bin(test_int);
    test_test_bin(test_float);
    test_test_bin(test_string);
    test_test_bin(test_vector);
    test_test_bin(test_list);
    test_test_bin(test_set);
    test_test_bin(test_map);
    test_test_bin(test_pair);
    
    test_test_bin(test_v_l);
    
    test_test_bin(test_i_m);

    Demo src,des;
    src.Init_r();
    src.cases.age = 99;
    
    test_test_bin(src);
    

}
void test_xml(){
    
    
    bool test_bool = true;
    char test_char = 'a';
    int test_int = 32;
    float test_float = 1.414;
    std::string test_string = "hello world";
    std::vector<int> test_vector = {1,2,3};
    std::list<int> test_list = {4,5,6};
    std::set<int> test_set = {7,8,9};
    std::map<int,std::string> test_map = {{1,"how"},{2,"are"},{3,"you"}};
    std::pair<std::string,std::string> test_pair = {"happy birthday", "to you!"};
    std::vector<std::list<int>> test_v_l = {{2,6,8,45,6},{898,7787,5454}};
    std::map<std::vector<int>,std::string> test_i_m = {{test_vector,"first is here"},{{7,45,88,954,}, "this is the second"}};
    std::list<std::vector<int>> test_l_v = {{2,6,8,45,6},{898,7787,5454}};
    std::set<std::list<int>> test_s_l = {{2,6,8,45,6},{898,7787,5454}};
    
    test_test_xml(test_bool);
    test_test_xml(test_char);
    test_test_xml(test_int);
    test_test_xml(test_float);
    test_test_xml(test_string);
    test_test_xml(test_vector);
    test_test_xml(test_list);
    test_test_xml(test_set);
    test_test_xml(test_map);
    test_test_xml(test_pair);
    
    test_test_xml(test_s_l);
    
    test_test_xml(test_i_m);

    Demo src,des;
    src.Init_r();
    src.cases.age = 99;
    
    test_test_xml(src);
    

}

int main(){
    std::cout << "\033[35m Starting DIY Binary tests:\033[0m" << std::endl;
    test_bin();
    std::cout << "\033[35m The XML tests are as follows\033[0m" << std::endl;
    test_xml();
    
    return 0;
}