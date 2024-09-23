#ifndef BINARY_HPP
#define BINARY_HPP

#include "include_file.h"
#include "base64.h"
using namespace std;

void int_double_bin();
void string_bin();
void pair_bin();
void vector_int_bin();
void vector_double_bin();
void vector_string_bin();
void list_int_bin();
void list_double_bin();
void list_string_bin();
void set_int_bin();
void set_double_bin();
void set_string_bin();
void map_intdouble_bin();
void map_intstr_bin();
void map_strint_bin();
void map_strstr_bin();
void UserDefinedType_bin();

void unique_ptr_bin();
void shared_ptr_bin();
void weak_ptr_bin();
void base64_help(string filename);

void test_base64();

struct UserDefinedType {
  int idx;
  string name;
  vector<double> data;
};

#define USE_BASE64_
#ifdef USE_BASE64_
#define PRINT_BASE64_ENCODE_DECODE(tar) {\
    std::string en_str = base64_encode(std::to_string(tar)); \
    std::string de_str = base64_decode(en_str); \
    std::cout << "base64_encode: " << en_str << std::endl; \
    std::cout << "base64_decode: " << de_str << std::endl; \
}
#else
#define PRINT_BASE64_ENCODE_DECODE(tar)
#endif

namespace binary
{
    
    //arithmetic---------------------------------------------
    template<class T>
    void serialize_bin(T& tar , string filename)
    {
        fstream file;
        file.open(filename, ios::app | ios::binary);
        file.write(reinterpret_cast<char*>(&tar), sizeof(tar));
        file.flush();
        file.close();
    }
    template<class T>
    void deserialize_bin(T& tar , string filename)
    {
        fstream file ; 
        file.open(filename, ios::in | ios::binary);
        file.read(reinterpret_cast<char*>(&tar), sizeof(tar));
        PRINT_BASE64_ENCODE_DECODE(tar);
        file.close();
    }
    //user------------------------------------------------
    
    inline void user_serialize(string filename)
    {
        return;
    }

    template<class T , class ...Args>
    inline void user_serialize(string filename , T item , Args ...remain)
    {
        serialize_bin(item , filename);
        user_serialize(filename , remain...);
    }
    
    //ptr-------------------------------------------------
    template<class T>
    void serialize_bin(unique_ptr<T>& tar , string filename)
    {
        fstream file;
        file.open(filename, ios::app | ios::binary);
        file.write(reinterpret_cast<char*>(&tar), sizeof(tar));
        file.flush();
        file.close();
    }
    

    template<class T>
    void serialize_bin(shared_ptr<T>& tar , string filename)
    {
        fstream file;
        file.open(filename, ios::app | ios::binary);
        file.write(reinterpret_cast<char*>(&tar), sizeof(tar));
        file.flush();
        file.close();
    }
    
    template<class T>
    void serialize_bin(weak_ptr<T>& tar , string filename)
    {
        fstream file;
        file.open(filename, ios::app | ios::binary);
        file.write(reinterpret_cast<char*>(&tar), sizeof(tar));
        file.flush();
        file.close();
    }
    //pair---------------------------------
    static void serialize_bin(pair<double , int> &tar, string filename)
    {
        fstream file;
        file.open(filename, ios::app | ios::binary);
        file.write(reinterpret_cast<char*>(&tar), sizeof(tar));
        file.flush();
        file.close();
    }
    
    static void deserialize_bin( pair<double , int> &tar, string filename)
    {
        fstream file ; 
        file.open(filename, ios::in | ios::binary);
        file.read(reinterpret_cast<char*>(&tar), sizeof(tar));
        
        file.close();
    }
    //string------------------------------
    
    static void serialize_bin(string& tar, string filename)
    {
        fstream file;
        file.open(filename, ios::app | ios::binary);
        int n = tar.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        file.write(tar.c_str(), n);
        file.flush();
        file.close();
    }
    
    static void deserialize_bin( string& tar, string filename)
    {
        fstream file;
        file.open(filename, ios::in | ios::binary);
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        tar.resize(n);
        file.read(const_cast<char*>(tar.c_str()), n);
        
        file.flush();
        file.close();
    }

    //vector-------------------------------------------
    static void deserialize(string& str, istream& file)
    {
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        str.resize(n); 
        file.read(const_cast<char*>(str.c_str()), n);
          
    }
     static void serialize(const string& str, ostream& file)
     {
        int n = str.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        file.write(str.c_str(), n);
          
    }
     template<class T>
    static void serialize(vector<T>& v, ostream& file)
    {
        int n = v.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& help : v)
        {
            file.write(reinterpret_cast<char*>(&help), sizeof(help));
        }
         
    }

    static void serialize(vector<string>& v, ostream& file)
    {
        int n = v.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& help : v){
            serialize(help, file);
        }
         
    }

    template<class T>
    void serialize_bin(vector<T>& v, string  filename)
    {
        fstream file;
        file.open( filename, ios::app | ios::binary);
        serialize(v, file);
        file.flush();
        file.close();
    }

    template<class T>
    static void deserialize(vector<T> &v, istream& file)
    {
        if(!file.eof()){
            v.clear();
            int n = 0;
            file.read(reinterpret_cast<char*>(&n), sizeof(n));
            for(int i=0; i<n; i++)
            {
                T temp = 0;
                file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
                v.emplace_back(temp);
            }
             
        }
    }

    static void deserialize(vector<string> &v, istream& file)
    {
        v.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++)
        {
            string str;
            deserialize(str, file);
            v.emplace_back(str);
        }
         
    }

    template<class T>
    void deserialize_bin(vector<T> &v, string  filename)
    {
        fstream file;
        file.open( filename, ios::in | ios::binary);
        deserialize(v, file);
        
        file.flush();
        file.close();
          
    }

    //list_----------------------------------------
    template<class T>
    static void serialize(list<T>&  list, ostream& file)
    {
        int n =  list.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& help :  list)
        {
            file.write(reinterpret_cast<char*>(&help), sizeof(help));
        }
         
    }

    static void serialize(list<string>&  list, ostream& file)
    {
        int n =  list.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& help :  list)
        {
            serialize(help, file);
        }
         
    }

    template<class T>
    void serialize_bin(list<T>&  list, string  filename)
    {
        fstream file;
        file.open( filename, ios::app | ios::binary);
        serialize( list, file);
        file.flush();
        file.close();
    }

    template<class T>
    static void deserialize(list<T>&  list, istream& file)
    {
        list.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++)
        {
            T help;
            file.read(reinterpret_cast<char*>(&help), sizeof(help));
            list.emplace_back(help);
        }
         
    }


    static void deserialize(list<string>&  list, istream& file)
    {
        list.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++)
        {
            string str;
            deserialize(str, file);
             list.emplace_back(str);
        }
         
    }

    template<class T> 
    void deserialize_bin(list<T>&  list, string  filename)
    {
        fstream file;
        file.open( filename, ios::in | ios::binary);

        deserialize( list, file);
        file.flush();
        file.close();
    }

    //set-----------------------------------------------------

    template<class T>
    static void serialize(set<T>&  my_set, ostream& file)
    {
        int n =  my_set.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& help :  my_set)
        {
            T * p = const_cast<T*>(&help);
            file.write(reinterpret_cast<char*>(p), sizeof(help));
        }
         
    }

    static void serialize(set<string>&  my_set, ostream& file)
    {
        int n =  my_set.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& help :  my_set)
        {
            serialize(help, file);
        }
         
    }

    template<class T>
    void serialize_bin(set<T>&  my_set, string filename)
    {
        fstream file;
        file.open(filename, ios::app | ios::binary);
        serialize( my_set, file);
        file.flush();
        file.close();
    }

    template<class T>
    static void deserialize(set<T>&  my_set, istream& file)
    {
        my_set.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++){
            T help;
            file.read(reinterpret_cast<char*>(&help), sizeof(help));
            my_set.insert(help);
        }
         
    }


    static void deserialize(set<string>&  my_set, istream& file)
    {
        my_set.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++){
            string str;
            deserialize(str, file);
            my_set.insert(str);
        }
         
    }

    template<class T> 
    void deserialize_bin(set<T>&  my_set, string  filename)
    {
        fstream file;
        file.open( filename, ios::in | ios::binary);

        deserialize( my_set, file);
        file.flush();
        file.close();
    }
    //map----------------------------------------------------

    template<class A, class B>
    static void serialize(map<A,B>& m, ostream& file)
    {
        int n = m.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& item : m)
        {
            A* ptrA = const_cast<A*>(&(item.first));
            file.write(reinterpret_cast<char*>(ptrA), sizeof(item.first));
            B* ptrB = const_cast<B*>(&(item.second));
            file.write(reinterpret_cast<char*>(ptrB),sizeof(item.second));
        }
         
    }

    template<class T>
    static void serialize(map<T,string>& m, ostream& file)
    {
        int n = m.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& item : m)
        {
            T* ptr;
            ptr = const_cast<T*>(&(item.first));
            file.write(reinterpret_cast<char*>(ptr), sizeof(item.first));
            serialize(item.second, file);
        }
         
    }

    template<class T>
    static void serialize(map<string,T>& m, ostream& file)
    {
        int n = m.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& item : m)
        {
            serialize(item.first, file);
            T* ptr;
            ptr = const_cast<T*>(&(item.second));
            file.write(reinterpret_cast<char*>(ptr), sizeof(item.second));
        }
         
    }

    static void serialize(map<string, string>& m, ostream& file)
    {
        int n = m.size();
        file.write(reinterpret_cast<char*>(&n), sizeof(n));
        for(auto& item : m){
            serialize(item.first, file);
            serialize(item.second, file);
        }
         
    }

    template<class A, class B>
    static void serialize_bin(map<A,B>& m, string fileName)
    {
        fstream file;
        file.open(fileName, ios::app | ios::binary);
        serialize(m, file);
        file.flush();
        file.close();
    }

    template<class A, class B>
    static void deserialize(map<A,B>& m, istream& file)
    {
        m.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++)
        {
            A temp1;
            file.read(reinterpret_cast<char*>(&temp1), sizeof(temp1));
            B temp2;
            file.read(reinterpret_cast<char*>(&temp2), sizeof(temp2));
            m.insert(pair<A,B>(temp1, temp2));
        }
        return;
    }

    template<class T>
    static void deserialize(map<T,string>& m, istream& file)
    {
        m.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++)
        {
            T temp;
            file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
            string temps;
            deserialize(temps, file);
            m.insert(pair<T,string>(temp, temps));
        }
        return;
    }

    template<class T>
    static void deserialize(map<string,T>& m, istream& file)
    {
        m.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++)
        {
            string temp;
            deserialize(temp, file);
            T temp2;
            file.read(reinterpret_cast<char*>(&temp2), sizeof(temp2));
            m.insert(pair<string,T>(temp, temp2));
        }
        return;
    }

    static void deserialize(map<string,string>& m, istream& file)
    {
        m.clear();
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(n));
        for(int i=0; i<n; i++)
        {
            string temp1;
            deserialize(temp1, file);
            string temp2;
            deserialize(temp2, file);
            m.insert(pair<string,string>(temp1, temp2));
        }
        return;
    } 

    template<class A, class B>
    void deserialize_bin(map<A,B>& m, string fileName)
    {
        fstream file;
        file.open(fileName, ios::in | ios::binary);
        deserialize(m, file);
        file.flush();
        file.close();
    }


}
#endif