#ifndef TO_XML_H
#define TO_XML_H
#include <string>
#include "Seelxml.h"
#include "../thirdparty/tinyxml2.h"
using namespace tinyxml2;



namespace xml{
    const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    static XMLDocument* doc_ptr = nullptr;
    XMLDocument* InitXML(){
        XMLError res;
        XMLDocument* doc = new XMLDocument();
        res = doc->Parse(declaration);
        doc_ptr = doc;
        return doc;
    }
    template <typename T>
    bool serialize(const T& src, const std::string& file){
         if(is_valid_type<T> == Type::OTHER && !is_user_defined<T>::value)
             throw "Not valid type! at serialize()";
        XMLDocument* doc = InitXML();

        //std::cout << "init completed" << std::endl;

        XMLElement* root = doc->NewElement("Serializer");
        doc->InsertEndChild(root);
        Seelxml::serialize(src, doc, root);
        doc->SaveFile(file.c_str());
        delete doc_ptr;
        doc_ptr = nullptr;
        return true;
    }
    template <typename T>
    bool deserialize(T& src, const std::string& file){
        
        XMLDocument* doc = new XMLDocument();
        // << doc->LoadFile(file.c_str()) << std::endl;
        doc->LoadFile(file.c_str());
        XMLElement* root = doc->FirstChildElement("Serializer");
        Seelxml::deserialize(src,root);
        
        delete doc;
        return true;
    }
    



}
#endif