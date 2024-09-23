#ifndef _XML_HPP
#define _XML_HPP

#include "include_file.h"
#include "tinyxml2.h"
#include "base64.h"

using namespace tinyxml2;
using namespace std;

void int_double_xml();
void string_xml();
void pair_intdouble_xml();
void vector_int_xml();
void vector_double_xml();
void vector_string_xml();
void list_int_xml();
void list_double_xml();
void list_string_xml();
void set_int_xml();
void set_double_xml();
void set_string_xml();
void map_intdouble_xml();
void map_intstr_xml();
void map_strint_xml();
void map_strstr_xml();
void UserDefinedType_xml();

void unique_ptr_xml();
void shared_ptr_xml();
void weak_ptr_xml();
void base64_help(string filename);

void test_base64();

struct UserDefinedType 
{
    int idx;
    string name;
    vector<double> data;
};

namespace xml
{
    class myxml_use
    {
        private:
            XMLDocument doc;
            XMLElement *root;

        void reset()
        {
            doc.Clear();
            XMLDeclaration * dec = doc.NewDeclaration("xml version \"1.0\" encoding = \"UTF-8\"");
            doc.InsertFirstChild(dec);
            root = doc.NewElement("serialization");
            doc.InsertEndChild(root);
        }
        void save(string filename)
        {
            doc.SaveFile(filename.c_str());
        }

        public:

        myxml_use()
        {
            reset();
        }
        //ptr
        

        template<class T>
        void serialize_xml(const T& object , string filename)
        {
            reset();
            serialize(object, root);
            save(filename);
        }

        bool deserialize_xml(bool& object , string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file"<<endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");

            bool ret2 = deserialize(object , root->FirstChildElement("bool_xml"));
            if( ! ret2)
            {
                cout<<"We can't find this file"<<endl;
                return false;
            }
            return true;
        }

        bool deserialize_xml(char& object , string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file"<<endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");

            bool ret2 = deserialize(object , root->FirstChildElement("char_xml"));
            if( ! ret2)
            {
                cout<<"We can't find this file"<<endl;
                return false;
            }
            return true;
        }

        bool deserialize_xml(int& object , string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file"<<endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");

            bool ret2 = deserialize(object , root->FirstChildElement("int_xml"));
            if( ! ret2)
            {
                cout<<"We can't find this file"<<endl;
                return false;
            }
            return true;
        }

        bool deserialize_xml(double& object , string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file"<<endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");

            bool ret2 = deserialize(object , root->FirstChildElement("double_xml"));
            if( ! ret2)
            {
                cout<<"We can't find this file"<<endl;
                return false;
            }
            return true;
        }

        bool deserialize_xml(string& object , string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file"<<endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");

            bool ret2 = deserialize(object , root->FirstChildElement("string_xml"));
            if( ! ret2)
            {
                cout<<"We can't find this file"<<endl;
                return false;
            }
            return true;
        }

        //pair--------------------------------------------------
        template<class A, class B>
        void serialize_xml(const pair<A, B>& p, string filename)
        {
            reset();
            serialize(p, root);
            save(filename);
 
        }
        template<class A, class B>
        bool deserialize_xml(pair<A, B>& p, string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file" << endl;
                return false;
            }
            root = doc.FirstChildElement("serialization");
            bool ret2 = deserialize(p, root->FirstChildElement("pair_xml"));
            if(! ret2)
            {
                cout << "We can't find this file" << endl;
                return false;
            }
            return true;
        }
        //vector--------------------------------
        template<class T>
        void serialize_xml(const vector<T>& vec, string filename)
        {
            reset();
            serialize(vec, root);
            save(filename);
        }

        template<class T>
        bool deserialize_xml(vector<T>& vec, string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout << "We can't open this file" << endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");
            bool ret2 = deserialize(vec, root->FirstChildElement("vector_xml"));
            if(! ret2)
            {
                cout << "We can't find this file" << endl;
                return false;
            }
            return true;
        }
        //list----------------------------------------
        template<class T>
        void serialize_xml(const list<T>& l, string filename)
        {
            reset();
            serialize(l, root);
            save(filename);
        }
        template<class T>
        bool deserialize_xml(list<T>& l, string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout << "We can't open this file" << endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");
            bool ret2 = deserialize(l, root->FirstChildElement("list_xml"));
            if(! ret2)
            {
                cout << "We can't find this file" << endl;
                return false;
            }
            return true;
        }
        
        //set---------------------------------------
        template<class T>
        void serialize_xml(const set<T>& s, string filename)
        {
            reset();
            serialize(s, root);
            save(filename);
        }
        template<class T>
        bool deserialize_xml(set<T>& s, string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout << "We can't open this file" << endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");
            bool ret2 = deserialize(s, root->FirstChildElement("set_xml"));
            if(! ret2)
            {
                cout << "We can't find this file" << endl;
                return false;
            }
            return true;
        }

        //map-------------------------------------------------
        template<class A, class B>
        void serialize_xml(const map<A,B>& m, string filename)
        {
            reset();
            serialize(m, root);
            save(filename);
        }
        template<class A, class B>
        bool deserialize_xml(map<A,B>& m, string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout << "We can't open this file" << endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");
            bool ret2 = deserialize(m, root->FirstChildElement("map_xml"));
            if(! ret2)
            {
                cout << "We can't find this file" << endl;
                return false;
            }
            return true;
        }

        

        private:

        void serialize(const bool& object, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("bool_xml");
            item->SetAttribute("value", to_string(object).c_str());
            node->InsertEndChild(item);
        }

        void serialize(const char& object, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("char_xml");
            item->SetAttribute("value", to_string(object).c_str());
            node->InsertEndChild(item);
        }

        void serialize(const int& object, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("int_xml");
            item->SetAttribute("value", to_string(object).c_str());
            node->InsertEndChild(item);
        }

        void serialize(const double& object, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("double_xml");
            item->SetAttribute("value", to_string(object).c_str());
            node->InsertEndChild(item);
        }

        void serialize(const string& object, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("string_xml");
            item->SetAttribute("value", (object).c_str());
            node->InsertEndChild(item);
        }
        

        bool deserialize(string& object, XMLElement* node){
            if(node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = value;
            return true;
        }

        bool deserialize(char& object, XMLElement* node){
            if(node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = stoi(value);
            return true;
        }

        bool deserialize(bool& object, XMLElement* node){
            if(node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = stoi(value);
            return true;
        }

        bool deserialize(int& object, XMLElement* node){
            if(node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = stoi(value);
            return true;
        }

        bool deserialize(double& object, XMLElement* node){
            if(node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            object = stod(value);
            return true;
        }
        //pair---------------------------------------------
        template<class A,class B>
        void serialize(const pair<A,B>& par, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("pair_xml");
            XMLElement* p1 = doc.NewElement("one");
            serialize(par.first, p1);
            item->InsertFirstChild(p1);
            XMLElement* p2 = doc.NewElement("two");
            serialize(par.second, p2);
            item->InsertEndChild(p2);
            node->InsertEndChild(item);
  
        }

        template<class A,class B>
        bool deserialize(pair<A,B>& par, XMLElement* node)
        {
            if(node == nullptr)
            {
                return false;
            }
            XMLElement* p1 = node->FirstChildElement("one");
            deserialize(par.first, p1->FirstChild()->ToElement());
            XMLElement* p2 = node->FirstChildElement("two");
            deserialize(par.second, p2->FirstChild()->ToElement());
            return true;
        }
        //vector----------------------------------------------
        template<class T>
        void serialize(const vector<T>& vec, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("vector_xml");
            item->SetAttribute("size", to_string(vec.size()).c_str());
            node->InsertEndChild(item);
            for(auto& elem: vec)
            {
                serialize(elem, item);
            }
        }

        template<class T>
        bool deserialize(vector<T>& vec, XMLElement* node)
        {
            if(node == nullptr)
            {
                return false;
            }
            XMLElement* child = node->FirstChild()->ToElement();
            for(int i=0; i<atoi(node->Attribute("size")); i++)
            {
                T  item;
                deserialize(item, child);
                vec.emplace_back(item);
                if(child->NextSibling())
                {
                    child = child->NextSibling()->ToElement();
                }
            }
            return true;
        }

        //list---------------------------------------------------
        template<class T>
        void serialize(const list<T>& l, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("list_xml");
            item->SetAttribute("size", to_string(l.size()).c_str());
            node->InsertEndChild(item);
            for(auto& elem: l)
            {
                serialize(elem, item);
            }
        }
        template<class T>
        bool deserialize(list<T>& l, XMLElement* node)
        {
            if(node == nullptr)
            {
                return false;
            }
            XMLElement* child = node->FirstChild()->ToElement();
            for(int i=0; i<atoi(node->Attribute("size")); i++)
            {
                T  item;
                deserialize(item, child);
                l.push_back(item);
                if(child->NextSibling())
                {
                    child = child->NextSibling()->ToElement();
                }
            }
            return true;
        }
        
        //set-----------------------------------------------
        template<class T>
        void serialize(const set<T>& s, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("set_xml");
            item->SetAttribute("size", to_string(s.size()).c_str());
            node->InsertEndChild(item);
            for(auto& elem: s)
            {
                serialize(elem, item);
            }
        }
        template<class T>
        bool deserialize(set<T>& s, XMLElement* node)
        {
            if(node == nullptr)
            {
                return false;
            }
            XMLElement* child = node->FirstChild()->ToElement();
            for(int i=0; i<atoi(node->Attribute("size")); i++)
            {
                T  item;
                deserialize(item, child);
                s.insert(item);
                if(child->NextSibling())
                {
                    child = child->NextSibling()->ToElement();
                }
            }
            return true;
        }

        //map------------------------------------------------
        template<class A, class B>
        void serialize(const map<A,B>& m, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("map_xml");
            item->SetAttribute("size", to_string(m.size()).c_str());
            node->InsertFirstChild(item);
            for(auto& elem : m)
            {
                serialize(make_pair(elem.first, elem.second), item);
            }
        }
        template<class A, class B>
        bool deserialize(map<A,B>& m, XMLElement* node)
        {
            if(node == nullptr){
                return false;
            }
            XMLElement* child = node->FirstChild()->ToElement();
            for(int i=0; i<atoi(node->Attribute("size")); i++){
                pair<A,B> p;
                deserialize(p, child);
                m.insert(p);
                if(child->NextSibling()){
                    child = child->NextSibling()->ToElement();
                }
            }
            return true;
        }

        //user---------------------------------------------------
        public:
        template<class... Args>
        void user_serialized_xml(string filename , Args... remain)
        {
            reset();
            user_serialized(filename , remain...);
        }
        template<class T , class... Args>
        void user_serialized(string filename , T tar  , Args...remain)
        {
            serialize(tar , root);
            user_serialized(filename , remain...);
        }
        
        void user_serialized(string filename)
        {
            save(filename);
        }


        //unique----------------------------
        template<class T>
        bool deserialize_xml(unique_ptr<T>& object , string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file"<<endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");

            bool ret2 = deserialize(object , root->FirstChildElement("unique_ptr_xml"));
            if( ! ret2)
            {
                cout<<"We can't find this file"<<endl;
                return false;
            }
            return true;
        }
        template<class T>
        void serialize(const unique_ptr<T>& object, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("unique_ptr_xml");
            item->SetAttribute("value", to_string(*object).c_str());
            node->InsertEndChild(item);
        }

        template<class T>
        bool deserialize(unique_ptr<T>& object, XMLElement* node){
            if(node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            *object = stoi(value);
            return true;
        }

        //shared----------------------------------
        template<class T>
        bool deserialize_xml(shared_ptr<T>& object , string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file"<<endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");

            bool ret2 = deserialize(object , root->FirstChildElement("shared_ptr_xml"));
            if( ! ret2)
            {
                cout<<"We can't find this file"<<endl;
                return false;
            }
            return true;
        }
        template<class T>
        void serialize(const shared_ptr<T>& object, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("shared_ptr_xml");
            item->SetAttribute("value", to_string(*object).c_str());
            node->InsertEndChild(item);
        }

        template<class T>
        bool deserialize(shared_ptr<T>& object, XMLElement* node){
            if(node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            *object = stoi(value);
            return true;
        }
        //weak------------------------------------------------------
        template<class T>
        bool deserialize_xml(weak_ptr<T>& object , string filename)
        {
            XMLError ret = doc.LoadFile(filename.c_str());
            if(ret != 0)
            {
                cout<<"We can't open this file"<<endl;
                return false;
            }

            root = doc.FirstChildElement("serialization");

            bool ret2 = deserialize(object , root->FirstChildElement("weak_ptr_xml"));
            if( ! ret2)
            {
                cout<<"We can't find this file"<<endl;
                return false;
            }
            return true;
        }
        template<class T>
        void serialize(const weak_ptr<T>& object, XMLElement* node)
        {
            XMLElement* item = doc.NewElement("weak_ptr_xml");
            item->SetAttribute("value", to_string(*object).c_str());
            node->InsertEndChild(item);
        }

        template<class T>
        bool deserialize(weak_ptr<T>& object, XMLElement* node){
            if(node == nullptr){
                return false;
            }
            string value = node->Attribute("value");
            *object = stoi(value);
            return true;
        }
        // template<class... Args>
        // void user_deserialized_xml(string filename , Args... remain)
        // {
        //     XMLError ret = doc.LoadFile(filename.c_str());
        //     if(ret != 0)
        //     {
        //         cout<<"We can't open this file"<<endl;
        //         return false;
        //     }

        //     root = doc.FirstChildElement("serialization");

        //     bool ret2 = deserialize(object , root->FirstChildElement("double_xml"));
        //     if( ! ret2)
        //     {
        //         cout<<"We can't find this file"<<endl;
        //         return false;
        //     }
        //     return true;
        // }
        // template<class T , class... Args>
        // void user_deserialized(string filename , T tar  , Args...remain)
        // {
            
        // }
        
        // void user_serialized(string filename)
        // {

        //     //save(filename);
        // }

    };
}

#endif