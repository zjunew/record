#ifndef SEELXML_H
#define SEELXML_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <utility>
#include <map>

#include "../thirdparty/tinyxml2.h"
#include "Typefigure.h"
#include "Reflection.h"
//#include "MACRO_EX.h"

using namespace tinyxml2;

#define XML_ATMOIC_CTOR         XMLElement* sub_root = doc->NewElement(tname.c_str());      \
                                root->InsertEndChild(sub_root);                             \
                                sub_root->SetAttribute("value", data);                      \
                                return 1;

namespace Seelxml{

    template <typename T>
    int serialize_node(const T& src, XMLDocument* doc,XMLElement* root);
    template <typename T,typename... type>
    int serialize_node(const std::list<T,type...>& data, XMLDocument* doc,XMLElement* root);
    template <typename T,typename... type>
    int serialize_node(const std::vector<T,type...>& data, XMLDocument* doc,XMLElement* root);
    
    template <typename T,typename... type>
    int serialize_node(const std::set<T,type...>& data, XMLDocument* doc,XMLElement* root);
    template <typename T,typename K>
    int serialize_node(const std::map<T, K>& data, XMLDocument* doc,XMLElement* root);
    template <typename T,typename K>
    int serialize_node(const std::pair<T,K>& data, XMLDocument* doc,XMLElement* root);

    template <typename T>
     XMLError deserialize_node(T& src, XMLElement* root);
     template <typename T>
      XMLError deserialize_node(std::vector<T>& src, XMLElement* root);
      template <typename T>
     XMLError deserialize_node(std::set<T>& src, XMLElement* root);
     template <typename T>
     XMLError deserialize_node(std::list<T>& src, XMLElement* root);
     template <typename T, typename K>
     XMLError deserialize_node(std::pair<T,K>& src, XMLElement* root);
     template <typename T, typename K>
     XMLError deserialize_node(std::map<T,K>& src, XMLElement* root);
     template <typename T>
    XMLError deserialize_node(T& data, XMLElement* root);



    template <typename T>
     int serialize_node(const T& src, XMLDocument* doc,XMLElement* root){
        int step = 0;
        XMLElement* sub_root = doc->NewElement(ClassName<T>());
        root->InsertEndChild(sub_root);
        for(int i=0;i< std::tuple_size<std::decay_t<decltype(struct_schema<T>)>>::value;i++){
            ForField(src,i,[&step, &sub_root, &doc](auto& field, auto& name){
                step+= serialize_node(field, doc, sub_root);
            });
        }
        return step;
    }

    template <>
    int serialize_node(const bool& data, XMLDocument* doc,XMLElement* root){std::string tname = "bool"; XML_ATMOIC_CTOR}

    template <>
    int serialize_node(const char& data, XMLDocument* doc,XMLElement* root){std::string tname = "char"; XML_ATMOIC_CTOR}

    template <>
    int serialize_node(const int& data, XMLDocument* doc,XMLElement* root){std::string tname = "int"; XML_ATMOIC_CTOR}

    template <>
    int serialize_node(const float& data, XMLDocument* doc,XMLElement* root){std::string tname = "float"; XML_ATMOIC_CTOR}

    template <>
    int serialize_node(const std::string& data, XMLDocument* doc,XMLElement* root){
        std::string tname = "string"; 
        XMLElement* sub_root = doc->NewElement(tname.c_str());
        root->InsertEndChild(sub_root);
        sub_root->SetAttribute("value", data.c_str());
        return 1;
    }




    template <typename T,typename... type>
     int serialize_node(const std::vector<T,type...>& data, XMLDocument* doc,XMLElement* root){
        std::string tname = "std_vector";
        int step = 0;
        XMLElement* sub_root = doc->NewElement(tname.c_str());
        root->InsertEndChild(sub_root);
        for(auto& i : data){
            //std::cout << is_valid_type<std::decay_t<decltype(i)>> << std::endl;
            step+=Seelxml::serialize_node(i, doc, sub_root);
        }
            
        return step;
    }

    template <typename T, typename... type>
     int serialize_node(const std::set<T,type...>& data, XMLDocument* doc,XMLElement* root){
        std::string tname = "std_set";
        int step = 0;
        XMLElement* sub_root = doc->NewElement(tname.c_str());
        root->InsertEndChild(sub_root);
        for(auto& i : data)
            step+=Seelxml::serialize_node(i, doc, sub_root);
        return step;
    }

    template <typename T, typename... type>
     int serialize_node(const std::list<T,type...>& data, XMLDocument* doc,XMLElement* root){
        std::string tname = "std_list";
        int step = 0;
        XMLElement* sub_root = doc->NewElement(tname.c_str());
        root->InsertEndChild(sub_root);
        for(auto& i : data){
            step+=serialize_node(i, doc, sub_root);
        }
        return step;
    }

    template <typename T, typename K>
     int serialize_node(const std::pair<T,K>& data, XMLDocument* doc,XMLElement* root){
        std::string tname = "std_pair";
        int step = 0;
        XMLElement* sub_root = doc->NewElement(tname.c_str());
        root->InsertEndChild(sub_root);
        step+=serialize_node(data.first,doc, sub_root);
        step+=serialize_node(data.second,doc, sub_root);
        return step;
    }
    template <typename T, typename K>
     int serialize_node(const std::map<T,K>& data, XMLDocument* doc,XMLElement* root){
        std::string tname = "std_map";
        int step = 0;
        std::pair<T,K> temp;
        XMLElement* sub_root = doc->NewElement(tname.c_str());
        root->InsertEndChild(sub_root);
        for(auto& i : data){
            temp = i;
            step+=serialize_node(temp, doc, sub_root);
        }
        return step;
    }

    

    

    template <typename T>
      XMLError deserialize_node(std::vector<T>& src, XMLElement* root){
        XMLElement* sub = root->FirstChildElement();
        T temp;
        src.clear();
        XMLError k;
        while(sub){
            k = deserialize_node(temp, sub);
            if(k != XML_SUCCESS)
                return k;
            src.push_back(temp);
            sub = sub->NextSiblingElement();
        }
        return XML_SUCCESS;
    }
    template <typename T>
     XMLError deserialize_node(std::set<T>& src, XMLElement* root){
        XMLElement* sub = root->FirstChildElement();
        T temp;
        src.clear();
        XMLError k;
        while(sub){
            k = deserialize_node(temp, sub);
            if(k != XML_SUCCESS)
                return k;
            src.insert(temp);
            sub = sub->NextSiblingElement();
        }
        return XML_SUCCESS;
    }
    template <typename T>
     XMLError deserialize_node(std::list<T>& src, XMLElement* root){
        XMLElement* sub = root->FirstChildElement();
        T temp;
        src.clear();
        XMLError k;
        while(sub){
            k = deserialize_node(temp, sub);
            if(k != XML_SUCCESS)
                return k;
            src.push_back(temp);
            sub = sub->NextSiblingElement();
        }
        return XML_SUCCESS;
    }
    template <typename T, typename K>
     XMLError deserialize_node(std::pair<T,K>& src, XMLElement* root){
        XMLElement* sub = root->FirstChildElement();
        std::pair<T,K> temp;
        XMLError k;
        k = deserialize_node(temp.first, sub);
        if(k != XML_SUCCESS)
            return k;
        sub = sub->NextSiblingElement();
        k = deserialize_node(temp.second, sub);
        src = temp;
        return k;
    }
    template <typename T, typename K>
     XMLError deserialize_node(std::map<T,K>& src, XMLElement* root){
        std::pair<T,K> temp;
        XMLElement* sub = root->FirstChildElement();
        XMLError k;
        src.clear();
        while(sub){
            k = deserialize_node(temp, sub);
            if(k != XML_SUCCESS)
                return k;
            src.insert(temp);
            sub = sub->NextSiblingElement();
        }
        return k;
    }

    

    template <typename T>
    XMLError deserialize_node(T& data, XMLElement* root){
        XMLElement * sub_root = root->FirstChildElement();
        XMLError L;
        for(int i=0;i< std::tuple_size<std::decay_t<decltype(struct_schema<T>)>>::value;i++){
            ForField(data,i,[&sub_root, &L](auto& field, auto& name){
                L = deserialize_node(field, sub_root);
            });
            sub_root = sub_root->NextSiblingElement();
            if(L != XML_SUCCESS)
                return L;
        }
        return L;
        
    }

    template <>
    XMLError deserialize_node(bool& src, XMLElement* root){
        return root->QueryBoolAttribute("value",&src);
    }

    template <>
    XMLError deserialize_node(char& src, XMLElement* root){
        int des;
        XMLError res = root->QueryIntAttribute("value", &des);
        src = (char)des;
        return res;
    }

    template <>
    XMLError deserialize_node(int& src, XMLElement* root){
        return root->QueryIntAttribute("value", &src);
    }

    template <>
    XMLError deserialize_node(float& src, XMLElement* root){
        return root->QueryFloatAttribute("value", &src);
    }

    template <>
    XMLError deserialize_node(std::string& src, XMLElement* root){
        char* buffer = nullptr;
        XMLError tmp = root->QueryStringAttribute("value", (const char **)&buffer);
        src = buffer;
        return tmp;
    }
    template <typename T>
    int serialize(const T& src, XMLDocument* doc,XMLElement* root){
        return serialize_node(src, doc, root);
    }

    template <typename T>
    XMLError deserialize(T& src, XMLElement* root){
        XMLElement * sub_root;
        sub_root = root->FirstChildElement();
        //std::cout << "The test type is: " << sub_root->Name()<<std::endl;
        return deserialize_node(src, sub_root);     
    }
}
#endif // SEELXML_H