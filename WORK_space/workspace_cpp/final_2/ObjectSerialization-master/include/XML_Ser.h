#ifndef XML_SER_H
#define XML_SER_H

#include "Base64.h"
#include "tinyxml2.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>

#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>

class xml_ser {
  private:
    tinyxml2::XMLDocument doc;  // the xml file
    const char *FilePath;       // xml file path

  public:
    tinyxml2::XMLElement *root;  // xml's root
    xml_ser(const char *filepath) : FilePath(filepath) {
        if (doc.LoadFile(FilePath)) {     // load xml file
            std::fstream file(FilePath);  // if fail, create one
            file.close();
            doc.LoadFile(FilePath);
        }
        doc.Clear();
        root = doc.NewElement("serialization");
        doc.InsertFirstChild(root);  // xml's root
    }
    ~xml_ser() { doc.SaveFile(FilePath); }  // if end, save the xml file

    /* Arithmetic */
    template <typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value>::type Serializer(
        const Type &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("val", obj);
        parent->InsertEndChild(newNode);  // insert new node into the xml tree
    };

    /* bool */
    void Serializer(const bool &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        // if write bool without trans to 0/1, it will output string "true" or "false"
        // but when read in a bool, it just can get a 0 or 1.
        if (obj)
            newNode->SetAttribute("val", 1);
        else
            newNode->SetAttribute("val", 0);
        parent->InsertEndChild(newNode);
    };

    /* string */
    template <typename Type>
    typename std::enable_if<std::is_same<Type, std::string>::value>::type Serializer(
        const Type &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("val", obj.c_str());
        parent->InsertEndChild(newNode);
    };

    /* pair */
    template <typename Type1, typename Type2>
    void Serializer(const std::pair<Type1, Type2> &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        parent->InsertEndChild(newNode);
        Serializer(obj.first, "first", newNode);
        Serializer(obj.second, "second", newNode);
    };

    /* vector */
    template <typename Type>
    void Serializer(const std::vector<Type> &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("size", obj.size());
        parent->InsertEndChild(newNode);
        int count = 0;
        for (auto &i : obj)
            Serializer(i, "vector_" + std::to_string(count++), newNode);
    }

    /* list */
    template <typename Type>
    void Serializer(const std::list<Type> &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("size", obj.size());
        parent->InsertEndChild(newNode);
        int count = 0;
        for (auto &i : obj)
            Serializer(i, "list_" + std::to_string(count++), newNode);
    }

    /* set */
    template <typename Type>
    void Serializer(const std::set<Type> &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("size", obj.size());
        parent->InsertEndChild(newNode);
        int count = 0;
        for (auto &i : obj)
            Serializer(i, "set_" + std::to_string(count++), newNode);
    }

    /* map */
    template <typename Type1, typename Type2>
    void Serializer(const std::map<Type1, Type2, std::less<Type1>, std::allocator<std::pair<const Type1, Type2>>> &obj,
        std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("size", obj.size());
        parent->InsertEndChild(newNode);
        int count = 0;
        for (auto &i : obj)
            Serializer<Type1, Type2>(i, "map_" + std::to_string(count++), newNode);
    }

    /* unique_ptr */
    template <typename Type>
    void Serializer(const std::unique_ptr<Type> &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        parent->InsertEndChild(newNode);
        Serializer(*obj, "unique_ptr", newNode);
    }
    template <typename Type>
    void Serializer(
        const std::unique_ptr<Type[]> &obj, std::string NodeName, tinyxml2::XMLElement *parent, size_t len) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("size", len);
        parent->InsertEndChild(newNode);
        int count = 0;
        for (size_t i = 0; i < len; i++)
            Serializer(obj[i], "unique_ptra_" + std::to_string(count++), newNode);
    }

    /* shared_ptr */
    template <typename Type>
    void Serializer(const std::shared_ptr<Type> &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        parent->InsertEndChild(newNode);
        Serializer(*obj, "shared_ptr", newNode);
    }
    template <typename Type>
    void Serializer(
        const std::shared_ptr<Type[]> &obj, std::string NodeName, tinyxml2::XMLElement *parent, size_t len) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("size", len);
        parent->InsertEndChild(newNode);
        int count = 0;
        for (size_t i = 0; i < len; i++)
            Serializer(obj[i], "shared_ptr_" + std::to_string(count++), newNode);
    }

    /* ptr */
    template <typename Type>
    typename std::enable_if<std::is_pointer<Type>::value>::type Serializer(
        const Type &obj, std::string NodeName, tinyxml2::XMLElement *parent) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        parent->InsertEndChild(newNode);
        Serializer(*obj, "ptr", newNode);
    }

    /* ptra */
    template <typename Type>
    void Serializer(const Type *obj, std::string NodeName, tinyxml2::XMLElement *parent, size_t len) {
        tinyxml2::XMLElement *newNode = doc.NewElement(NodeName.c_str());
        newNode->SetAttribute("size", len);
        parent->InsertEndChild(newNode);
        int count = 0;
        for (size_t i = 0; i < len; i++)
            Serializer(obj[i], "ptra_" + std::to_string(count++), newNode);
    }
};

/*---------------------------------------------------------------------------*/

class xml_des {
  public:
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *root;
    std::stringstream buffer;
    const char *FilePath;
    xml_des(const char *filepath) : FilePath(filepath) {
        if (doc.LoadFile(FilePath)) {
            doc.PrintError();
            exit(1);
        }
        root = doc.RootElement();
    }
    ~xml_des() { doc.SaveFile(FilePath); }

    /* Arithmetic || string */
    template <typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value || std::is_same<Type, std::string>::value>::type
    Deserializer(Type &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        buffer << Node->FirstAttribute()->Value();
        buffer >> obj;
        buffer.clear();
    }

    /* pair */
    template <typename Type1, typename Type2>
    void Deserializer(std::pair<Type1, Type2> &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        Type1 tmp1;
        Type2 tmp2;
        Deserializer(tmp1, "first", Node->FirstChildElement());
        Deserializer(tmp2, "second", Node->FirstChildElement()->NextSiblingElement());
        obj = std::make_pair(tmp1, tmp2);
    };

    /* vector */
    template <typename Type>
    void Deserializer(std::vector<Type> &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        size_t len;
        buffer << Node->FirstAttribute()->Value();
        buffer >> len;
        buffer.clear();
        obj.resize(len);
        tinyxml2::XMLElement *nextNode = Node->FirstChildElement();
        int count                      = 0;
        for (auto &i : obj) {
            Deserializer(i, "vector_" + std::to_string(count++), nextNode);
            nextNode = nextNode->NextSiblingElement();
        }
    }

    /* list */
    template <typename Type>
    void Deserializer(std::list<Type> &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        size_t len;
        buffer << Node->FirstAttribute()->Value();
        buffer >> len;
        buffer.clear();
        obj.resize(len);
        tinyxml2::XMLElement *nextNode = Node->FirstChildElement();
        int count                      = 0;
        for (auto &i : obj) {
            Deserializer(i, "list_" + std::to_string(count++), nextNode);
            nextNode = nextNode->NextSiblingElement();
        }
    }

    /* set */
    template <typename Type>
    void Deserializer(std::set<Type> &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        size_t len;
        buffer << Node->FirstAttribute()->Value();
        buffer >> len;
        buffer.clear();
        tinyxml2::XMLElement *nextNode = Node->FirstChildElement();
        int count                      = 0;
        for (size_t i = 0; i < len; i++) {
            Type tmp;
            Deserializer(tmp, "set_" + std::to_string(count++), nextNode);
            obj.insert(tmp);
            nextNode = nextNode->NextSiblingElement();
        }
    }

    /* map */
    template <typename Type1, typename Type2>
    void Deserializer(std::map<Type1, Type2> &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        size_t len;
        buffer << Node->FirstAttribute()->Value();
        buffer >> len;
        buffer.clear();
        tinyxml2::XMLElement *nextNode = Node->FirstChildElement();
        for (size_t i = 0; i < len; i++) {
            Type1 tmp1;
            Type2 tmp2;
            Deserializer(tmp1, "map_first", nextNode->FirstChildElement());
            Deserializer(tmp2, "map_second", nextNode->FirstChildElement()->NextSiblingElement());
            obj.insert(std::make_pair(tmp1, tmp2));
            nextNode = nextNode->NextSiblingElement();
        }
    }

    /* unique_ptr */
    template <typename Type>
    void Deserializer(std::unique_ptr<Type> &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        obj = std::unique_ptr<Type>(new Type);
        Deserializer(*obj, "unique_ptr", Node->FirstChildElement());
    }
    template <typename Type>
    void Deserializer(std::unique_ptr<Type[]> &obj, std::string NodeName, tinyxml2::XMLElement *Node, size_t len) {
        obj                            = std::unique_ptr<Type[]>(new Type[len]);
        tinyxml2::XMLElement *nextNode = Node->FirstChildElement();
        int count                      = 0;
        for (size_t i = 0; i < len; i++) {
            Deserializer(obj[i], "unique_ptra_" + std::to_string(count++), nextNode);
            nextNode = nextNode->NextSiblingElement();
        }
    }

    /* shared_ptr */
    template <typename Type>
    void Deserializer(std::shared_ptr<Type> &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        obj = std::shared_ptr<Type>(new Type);
        Deserializer(*obj, "shared_ptr", Node->FirstChildElement());
    }
    template <typename Type>
    void Deserializer(std::shared_ptr<Type[]> &obj, std::string NodeName, tinyxml2::XMLElement *Node, size_t len) {
        obj                            = std::unique_ptr<Type>(new Type[len]);
        tinyxml2::XMLElement *nextNode = Node->FirstChildElement();
        int count                      = 0;
        for (size_t i = 0; i < len; i++) {
            Deserializer(obj[i], "shared_ptra_" + std::to_string(count++), nextNode);
            nextNode = nextNode->NextSiblingElement();
        }
    }

    /* ptr */
    template <typename Type>
    typename std::enable_if<std::is_pointer<Type>::value>::type Deserializer(
        const Type &obj, std::string NodeName, tinyxml2::XMLElement *Node) {
        // unlike smart pointer, when this function ends, it will die
        // so it need to be allocated outside
        Deserializer(*obj, "ptr", Node->FirstChildElement());
    }

    /* ptra */
    template <typename Type>
    void Deserializer(Type *obj, std::string NodeName, tinyxml2::XMLElement *Node, size_t len) {
        // obj = new Type[len];
        tinyxml2::XMLElement *nextNode = Node->FirstChildElement();
        int count                      = 0;
        for (size_t i = 0; i < len; i++) {
            Deserializer(obj[i], "ptra_" + std::to_string(count++), nextNode);
            nextNode = nextNode->NextSiblingElement();
        }
    }
};

#endif