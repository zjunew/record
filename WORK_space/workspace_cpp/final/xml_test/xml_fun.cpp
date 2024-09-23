#include "xml.hpp"

using namespace std;

const string output = "  ------------------------------  ";
void base64_help(string filename);
void int_double_xml()
{
    cout<<output<<"int_double_xml"<<output<<endl;
    xml::myxml_use ptr;
    int nums1 =100,nums2;
    ptr.serialize_xml(nums1 , "xml_generate\\int.xml");
    ptr.deserialize_xml(nums2 , "xml_generate\\int.xml");
    cout<<"nums1:"<<nums1<<endl;
    cout<<"nums2:"<<nums2<<endl;

    double dou1 =5.0,dou2;
    ptr.serialize_xml(dou1 , "xml_generate\\double.xml");
    ptr.deserialize_xml(dou2 , "xml_generate\\double.xml");
    cout<<"dou1:"<<dou1<<endl;
    cout<<"dou2:"<<dou2<<endl;
}
void string_xml()
{
    cout<<output<<"string_xml"<<output<<endl;
    xml::myxml_use ptr;
    string str1 = "world" , str2;
    ptr.serialize_xml(str1 , "xml_generate\\str.xml");
    ptr.deserialize_xml(str2 , "xml_generate\\str.xml");
    cout << "str1 :" << str1 << endl;
	cout << "str2 :" << str2 << endl;
	cout << "(str1 == str2)?1:0  Then output: " << (str1 == str2)?1:0 ;
	cout << endl;
}
void pair_intdouble_xml()
{
    cout<<output<<"pair_xml"<<output<<endl;
    xml::myxml_use ptr;
    pair<int  , double> p1 = {100 , 5.0};
    pair<int , double> p2;
    ptr.serialize_xml( p1, "xml_generate\\pairint_double.xml");
    ptr.deserialize_xml(p2 , "xml_generate\\pairint_double.xml");
    cout<<"p1.first: "<<p1.first<<" p1.second: "<<p1.second<<endl;
    cout<<"p2.first: "<<p2.first<<" p2.second: "<<p2.second<<endl;
	cout << "(p1 == p2)?1:0  Then output: " << ( p1== p2)?1:0 ;
	cout << endl;
}
void vector_int_xml()
{
    cout<<output<<"vector_int_xml"<<output<<endl;
    xml::myxml_use ptr;
    vector<int> v1 = {1,2,3};
    vector<int> v2;
    ptr.serialize_xml(v1 , "xml_generate\\vector_int.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\vector_int.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void vector_double_xml()
{
    cout<<output<<"vector_double_xml"<<output<<endl;
    xml::myxml_use ptr;
    vector<double> v1 = {1.1,2.2,3.3};
    vector<double> v2;
    ptr.serialize_xml(v1 , "xml_generate\\vector_double.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\vector_double.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void vector_string_xml()
{
    cout<<output<<"vector_string_xml"<<output<<endl;
    xml::myxml_use ptr;
    vector<string> v1 = {"Hello" , "world"};
    vector<string> v2;
    ptr.serialize_xml(v1 , "xml_generate\\vector_string.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\vector_string.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void list_int_xml()
{
    cout<<output<<"list_int_xml"<<output<<endl;
    xml::myxml_use ptr;
    list<int> v1 = {1,2,3,4};
    list<int> v2;
    ptr.serialize_xml(v1 , "xml_generate\\list_int.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\list_int.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void list_double_xml()
{
    cout<<output<<"list_double_xml"<<output<<endl;
    xml::myxml_use ptr;
    list<double> v1 = {1.1,2.2,3.3,4.4};
    list<double> v2;
    ptr.serialize_xml(v1 , "xml_generate\\list_double.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\list_double.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void list_string_xml()
{
    cout<<output<<"list_string_xml"<<output<<endl;
    xml::myxml_use ptr;
    list<string> v1 = {"Hello" , "world"};
    list<string> v2;
    ptr.serialize_xml(v1 , "xml_generate\\list_string.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\list_string.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void set_int_xml()
{
    cout<<output<<"set_int_xml"<<output<<endl;
    xml::myxml_use ptr;
    set<int> v1 = {1,2,3,4};
    set<int> v2;
    ptr.serialize_xml(v1 , "xml_generate\\set_int.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\set_int.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void set_double_xml()
{
    cout<<output<<"set_double_xml"<<output<<endl;
    xml::myxml_use ptr;
    set<double> v1 = {1.1,2.2,3.3};
    set<double> v2;
    ptr.serialize_xml(v1 , "xml_generate\\set_double.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\set_double.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void set_string_xml()
{
    cout<<output<<"set_string_xml"<<output<<endl;
    xml::myxml_use ptr;
    set<string> v1 = {"Hello" , "world"};
    set<string> v2;
    ptr.serialize_xml(v1 , "xml_generate\\set_string.xml");
    ptr.deserialize_xml(v2 , "xml_generate\\set_string.xml");
    for(auto iter1 = v1.begin(), iter2 = v2.begin() ;iter1 != v1.end() ; iter1++ , iter2++)
    {
        cout<<" iter1: "<<*iter1<<" iter2: "<<*iter2;
    }
    cout<<endl << "(v1 == v2)?1:0  Then output: " << (v1== v2)?1:0 ;
	cout << endl;
}
void map_intdouble_xml()
{
    cout<<output<<"map_intdouble_xml"<<output<<endl;
    map<int , double> mymap1 = {{1,1.1} , {2,2.2} , {3,3.3}};
    map<int , double> mymap2;
    xml::myxml_use ptr;
    ptr.serialize_xml(mymap1 , "xml_generate\\map_intdouble.xml");
    ptr.deserialize_xml(mymap2 , "xml_generate\\map_intdouble.xml");
    for(auto iter1 = mymap1.begin() , iter2 = mymap2.begin();iter1!=mymap1.end();iter1++,iter2++)
    {
        cout<<" map1: "<<(*iter1).first<<"  "<<(*iter1).second;
        cout<<" map2: "<<(*iter2).first<<"  "<<(*iter2).second<<endl;
    }
    cout<<endl<<"(mymap1==mymap2)?1:0 Then output:"<<(mymap1==mymap2)?1:0;
    cout<<endl;
}
void map_intstr_xml()
{
    cout<<output<<"map_intstr_xml"<<output<<endl;
    map<int , string> mymap1 = {{1,"Hello"} , {2,","} , {3,"world"}};
    map<int , string> mymap2;
    xml::myxml_use ptr;
    ptr.serialize_xml(mymap1 , "xml_generate\\map_intstr.xml");
    ptr.deserialize_xml(mymap2 , "xml_generate\\map_intstr.xml");
    for(auto iter1 = mymap1.begin() , iter2 = mymap2.begin();iter1!=mymap1.end();iter1++,iter2++)
    {
        cout<<" map1: "<<(*iter1).first<<"  "<<(*iter1).second;
        cout<<" map2: "<<(*iter2).first<<"  "<<(*iter2).second<<endl;
    }
    cout<<endl<<"(mymap1==mymap2)?1:0 Then output:"<<(mymap1==mymap2)?1:0;
    cout<<endl;
}
void map_strint_xml()
{
    cout<<output<<"map_strint_xml"<<output<<endl;
    map<string,int> mymap1 = {{"Hello" , 1}, {"world" , 2}};
    map<string,int> mymap2;
    xml::myxml_use ptr;
    ptr.serialize_xml(mymap1 , "xml_generate\\map_strint.xml");
    ptr.deserialize_xml(mymap2 , "xml_generate\\map_strint.xml");
    for(auto iter1 = mymap1.begin() , iter2 = mymap2.begin();iter1!=mymap1.end();iter1++,iter2++)
    {
        cout<<" map1: "<<(*iter1).first<<"  "<<(*iter1).second;
        cout<<" map2: "<<(*iter2).first<<"  "<<(*iter2).second<<endl;
    }
    cout<<endl<<"(mymap1==mymap2)?1:0 Then output:"<<(mymap1==mymap2)?1:0;
    cout<<endl;
}
void map_strstr_xml()
{
    cout<<output<<"map_strstr_xml"<<output<<endl;
    map<string,string> mymap1 = {{"Hello" , ","}, {"world" , " now"}};
    map<string,string> mymap2;
    xml::myxml_use ptr;
    ptr.serialize_xml(mymap1 , "xml_generate\\map_strstr.xml");
    ptr.deserialize_xml(mymap2 , "xml_generate\\map_strstr.xml");
    for(auto iter1 = mymap1.begin() , iter2 = mymap2.begin();iter1!=mymap1.end();iter1++,iter2++)
    {
        cout<<" map1: "<<(*iter1).first<<"  "<<(*iter1).second;
        cout<<" map2: "<<(*iter2).first<<"  "<<(*iter2).second<<endl;
    }
    cout<<endl<<"(mymap1==mymap2)?1:0 Then output:"<<(mymap1==mymap2)?1:0;
    cout<<endl;
}
void my_read(string filename)
{
    fstream file;
    file.open(filename);
    string line;
    cout<<output<<"This is the file"<<output<<endl;
     while (getline(file, line)) { // 逐行读取文件内容
        cout << line << endl; // 输出文件内容到控制台
    }

    file.close();
}
void UserDefinedType_xml()
{
    cout<<"             "<<"UserDefinedType_xml"<<"             "<<endl;
    UserDefinedType u1 ;
    u1.idx  = 1 ;
    u1.data = {100.0 , 5.0};
    u1.name = "Alice" ;
    xml::myxml_use ptr;
    ptr.user_serialized_xml("ptr_user_xml\\user.xml" , u1.data , u1.idx , u1.name);
    my_read("ptr_user_xml\\user.xml");
    // fstream file;
    // file.open("xml_generate\\user.xml");
    // string line;
    // cout<<output<<"This is the file"<<output<<endl;
    //  while (getline(file, line)) { // 逐行读取文件内容
    //     cout << line << endl; // 输出文件内容到控制台
    // }

    // file.close();
}
void unique_ptr_xml()
{
    cout<<output<<"unique_xml"<<output<<endl;
    xml::myxml_use ptr;
    unique_ptr<int> p (new int(10));
    ptr.serialize_xml(p , "ptr_user_xml\\unique_ptr.xml");
    my_read("ptr_user_xml\\unique_ptr.xml");
    cout<<"unique_ptr.data has been created."<<endl;
}

void shared_ptr_xml()
{
    cout<<output<<"shared_xml"<<output<<endl;
    xml::myxml_use ptr;
    shared_ptr<int> p (new int(10));
    //shared_ptr<int> q = p;
    ptr.serialize_xml(p , "ptr_user_xml\\shared_ptr.xml");
    my_read("ptr_user_xml\\shared_ptr.xml");
    cout<<"shared_ptr.data has been created."<<endl;
    //p.reset();
}
void weak_ptr_xml()
{
    cout<<output<<"weak_ptr_xml"<<output<<endl;
    xml::myxml_use ptr;
    shared_ptr<int> p (new int(10));
    weak_ptr<int> q = p;
    ptr.serialize_xml(q.lock() , "ptr_user_xml\\weak_ptr.xml");
    my_read("ptr_user_xml\\shared_ptr.xml");
    cout<<"weak_ptr.data has been created."<<endl;
    p.reset();
}
void base64_help(string filename)
{
    fstream file;
    file.open(filename);
    if(!file.is_open())
    {
        cout<<"We can't open this file"<<endl;
        return ;
    }
    string line , out;
    cout<<output<<"This is the file"<<output<<endl;
    while (getline(file, line)) 
    {
        out += line;
        out+='\n';
    }
    out.pop_back();
    string result = base64_encode(out);
    cout<<"The result of encode :"<<result<<endl;
    file.close();
    cout<<"Now we will decode:"<<endl;
    string de_result = base64_decode(result);
    cout<<de_result<<endl;
}

void test_base64()
{
    cout<<"We have accomplish xml , please input :"<<endl;
    
    cout<<"1.encode     other_input.exit"<<endl;
    unsigned char help ;
    cin>>help;
    while(help=='1')
    {
        cout<<"please input the filename : for example xml_generate\int.xml"<<endl;
        string name;
        cin>>name;
        base64_help(name);
        cout<<"We have accomplish this , please input :"<<endl;
        cout<<"1.encode     other.exit"<<endl;
        cin>>help;
    }
}