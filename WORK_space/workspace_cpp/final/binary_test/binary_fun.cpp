#include "binary.hpp"

using namespace std;


const string output = "  ------------------------------  ";

void unique_ptr_bin()
{
    cout<<output<<"unique_ptr_bin"<<output<<endl;
    unique_ptr<int> p1(new int(10)) ;
    binary::serialize_bin(p1 , "ptr_user_data\\unique_ptr.data");
    //binary::deserialize_bin(p2 , "bin_data\\unique_ptr.data");
    cout<<*p1<<endl;
    cout<<"unique_ptr.data has been created."<<endl;
}

void shared_ptr_bin()
{
    cout<<output<<"shared_ptr_bin"<<output<<endl;
    shared_ptr<int> p1(new int(10)) ;
    binary::serialize_bin(p1 , "ptr_user_data\\shared_ptr.data");
    //binary::deserialize_bin(p2 , "bin_data\\share_ptr.data");
    cout<<*p1<<endl;
    cout<<"shared_ptr.data has been created."<<endl;
}

void weak_ptr_bin()
{
    cout<<output<<"weak_ptr_bin"<<output<<endl;
    shared_ptr<int> p1(new int(10)) ;
    weak_ptr<int> p2 = p1;
    binary::serialize_bin(p2 , "ptr_user_data\\weak_ptr.data");
    //binary::deserialize_bin(p2 , "bin_data\\_ptr.data");
    cout<<"p2.expired(): "<<p2.expired()<<endl;
    cout<<"weak_ptr.data has been created."<<endl;
}

void UserDefinedType_bin()
{
    cout<<output<<"UserDefinedType_bin"<<output<<endl;
    UserDefinedType user1;

    user1.idx = 1011; 
    user1.name = "Alice";
    user1.data = {100,1};
    binary::user_serialize("ptr_user_data\\user.data" , user1.idx , user1.data , user1.name);
    
    cout<<"user.data has been created."<<endl;
}

void int_double_bin()
{
    cout<<output<<"int_double_bin"<<output<<endl;
    int num1 = 5  , num2;
    double dou1 = 1.0 , dou2; 
    binary::serialize_bin(num1 , "bin_data\\int.data");
    binary::deserialize_bin(num2 , "bin_data\\int.data");

    binary::serialize_bin(dou1 , "bin_data\\double.data");
    binary::deserialize_bin(dou2 , "bin_data\\double.data");

    cout<<"num1: "<<num1<<"   num2:"<<num2<<endl;
    cout<<"dou1: "<<dou1<<"   dou2:"<<dou2<<endl;
}

void string_bin()
{
    cout<<output<<"string_bin"<<output<<endl;
    string str1 = "oopfinal" , str2;
    binary::serialize_bin(str1 , "bin_data\\string.data");
    binary::deserialize_bin(str2 , "bin_data\\string.data");
    cout<< str1 << " is equal "<<str2 <<" \n(str1==str2)?1:0 Then output: "<<(str1==str2)?1:0;
    cout<<endl;
}

void pair_bin()
{
    cout<<output<<"pair_bin"<<output<<endl;
    pair<double , int> data1  = {5.0 , 100};
    pair<double , int> data2 ;
    binary::serialize_bin(data1 , "bin_data\\pair.data");
    binary::deserialize_bin(data2 , "bin_data\\pair.data");
    cout<<data1.first<<" "<<data1.second<<endl;
    cout<<data2.first<<" "<<data2.second<<endl;
    cout<<"(data1==data2)?1:0 Then output:"<<(data1==data2)?1:0;
    cout<<endl;
}

//vector------------------------------------------------

void vector_int_bin()
{
    cout<<output<<"vector_int_bin"<<output<<endl;
    vector<int> vect1={1,2,3,4,5};
    vector<int> vect2;
    binary::serialize_bin(vect1 , "bin_data\\vector_int.data");
    binary::deserialize_bin(vect2 , "bin_data\\vector_int.data");
    for(int i = 0 ; i < 5 ; i++ )
    {
        cout<<" vect1: "<<vect1[i] << " vect2: "<<vect2[i];
    }
    cout<<endl<<"(vect1==vect2)?1:0 Then output:"<<(vect1==vect2)?1:0;
    cout<<endl;
}
void vector_double_bin()
{
    cout<<output<<"vector_double_bin"<<output<<endl;
    vector<double> vect1={1.1,2.2,3.3,4.4,5.5};
    vector<double> vect2;
    binary::serialize_bin(vect1 , "bin_data\\vector_double.data");
    binary::deserialize_bin(vect2 , "bin_data\\vector_double.data");
    for(int i = 0 ; i < 5 ; i++ )
    {
        cout<<" vect1: "<<vect1[i] << " vect2: "<<vect2[i];
    }
    cout<<endl<<"(vect1==vect2)?1:0 Then output:"<<(vect1==vect2)?1:0;
    cout<<endl;
}
void vector_string_bin()
{
    cout<<output<<"vector_string_bin"<<output<<endl;
    vector<string> vect1={"1.1","2.2","3.3"};
    vector<string> vect2;
    binary::serialize_bin(vect1 , "bin_data\\vector_string.data");
    binary::deserialize_bin(vect2 , "bin_data\\vector_string.data");
    for(int i = 0 ; i < 3 ; i++ )
    {
        cout<<" vect1: "<<vect1[i] << " vect2: "<<vect2[i];
    }
    cout<<endl<<"(vect1==vect2)?1:0 Then output:"<<(vect1==vect2)?1:0;
    cout<<endl;
}

//list-----------------------------------------------------------

void list_int_bin()
{
    cout<<output<<"list_int_bin"<<output<<endl;
    list<int> list1={1,2,3};
    list<int> list2;
    binary::serialize_bin(list1 , "bin_data\\list_int.data");
    binary::deserialize_bin(list2 , "bin_data\\list_int.data");
    for(auto iter1 = list1.begin() , iter2 = list2.begin();iter1!=list1.end();iter1++,iter2++)
    {
        cout<<" list1: "<<*iter1<<" list2: "<<*iter2;
    }
    cout<<endl<<"(list1==list2)?1:0 Then output:"<<(list1==list2)?1:0;
    cout<<endl;
}
void list_double_bin()
{
    cout<<output<<"list_double_bin"<<output<<endl;
    list<double> list1={1.1,2.2,3.3};
    list<double> list2;
    binary::serialize_bin(list1 , "bin_data\\list_double.data");
    binary::deserialize_bin(list2 , "bin_data\\list_double.data");
    for(auto iter1 = list1.begin() , iter2 = list2.begin();iter1!=list1.end();iter1++,iter2++)
    {
        cout<<" list1: "<<*iter1<<" list2: "<<*iter2;
    }
    cout<<endl<<"(list1==list2)?1:0 Then output:"<<(list1==list2)?1:0;
    cout<<endl;
}
void list_string_bin()
{
    cout<<output<<"list_string_bin"<<output<<endl;
    list<string> list1={"1.1" , "2.2" , "3.3"};
    list<string> list2;
    binary::serialize_bin(list1 , "bin_data\\list_string.data");
    binary::deserialize_bin(list2 , "bin_data\\list_string.data");
    for(auto iter1 = list1.begin() , iter2 = list2.begin();iter1!=list1.end();iter1++,iter2++)
    {
        cout<<" list1: "<<*iter1<<" list2: "<<*iter2;
    }
    cout<<endl<<"(list1==list2)?1:0 Then output:"<<(list1==list2)?1:0;
    cout<<endl;
}

//set---------------------------------------------------------

void set_int_bin()
{
    cout<<output<<"set_int_bin"<<output<<endl;
    set<int> myset1={1,2,3,4,5};
    set<int> myset2;
    binary::serialize_bin(myset1 , "bin_data\\set_int.data");
    binary::deserialize_bin(myset2 , "bin_data\\set_int.data");
    for(auto iter1 = myset1.begin() , iter2 = myset2.begin();iter1!=myset1.end();iter1++,iter2++)
    {
        cout<<" set1: "<<*iter1<<" set2: "<<*iter2;
    }
    cout<<endl<<"(myset1==myset2)?1:0 Then output:"<<(myset1==myset2)?1:0;
    cout<<endl;
}
void set_double_bin()
{
    cout<<output<<"set_double_bin"<<output<<endl;
    set<double> myset1={1.1,2.2,3.3,4.4,5.5};
    set<double> myset2;
    binary::serialize_bin(myset1 , "bin_data\\set_double.data");
    binary::deserialize_bin(myset2 , "bin_data\\set_double.data");
    for(auto iter1 = myset1.begin() , iter2 = myset2.begin();iter1!=myset1.end();iter1++,iter2++)
    {
        cout<<" set1: "<<*iter1<<" set2: "<<*iter2;
    }
    cout<<endl<<"(myset1==myset2)?1:0 Then output:"<<(myset1==myset2)?1:0;
    cout<<endl;
}
void set_string_bin()
{
    cout<<output<<"set_string_bin"<<output<<endl;
    set<string> myset1={"1.1,2.2,3.3,4.4,5.5" , "world"};
    set<string> myset2;
    binary::serialize_bin(myset1 , "bin_data\\set_string.data");
    binary::deserialize_bin(myset2 , "bin_data\\set_string.data");
    for(auto iter1 = myset1.begin() , iter2 = myset2.begin();iter1!=myset1.end();iter1++,iter2++)
    {
        cout<<" set1: "<<*iter1<<" set2: "<<*iter2;
    }
    cout<<endl<<"(myset1==myset2)?1:0 Then output:"<<(myset1==myset2)?1:0;
    cout<<endl;
}

//map-----------------------------------------------------------------

void map_intdouble_bin()
{
    cout<<output<<"map_intdouble_bin"<<output<<endl;
    map<int , double> mymap1 = {{1,1.1} , {2,2.2} , {3,3.3}};
    map<int , double> mymap2;
    binary::serialize_bin(mymap1 , "bin_data\\map_intdouble.data");
    binary::deserialize_bin(mymap2 , "bin_data\\map_intdouble.data");
    for(auto iter1 = mymap1.begin() , iter2 = mymap2.begin();iter1!=mymap1.end();iter1++,iter2++)
    {
        cout<<" map1: "<<(*iter1).first<<"  "<<(*iter1).second;
        cout<<" map2: "<<(*iter2).first<<"  "<<(*iter2).second<<endl;
    }
    cout<<endl<<"(mymap1==mymap2)?1:0 Then output:"<<(mymap1==mymap2)?1:0;
    cout<<endl;
}
void map_intstr_bin()
{
    cout<<output<<"map_intdouble_bin"<<output<<endl;
    map<int , string> mymap1 = {{1,"welcome"} , {2,"to"} , {3,"the"}};
    map<int , string> mymap2;
    binary::serialize_bin(mymap1 , "bin_data\\map_intstr.data");
    binary::deserialize_bin(mymap2 , "bin_data\\map_intstr.data");
    for(auto iter1 = mymap1.begin() , iter2 = mymap2.begin();iter1!=mymap1.end();iter1++,iter2++)
    {
        cout<<" map1: "<<(*iter1).first<<"  "<<(*iter1).second;
        cout<<" map2: "<<(*iter2).first<<"  "<<(*iter2).second<<endl;
    }
    cout<<endl<<"(mymap1==mymap2)?1:0 Then output:"<<(mymap1==mymap2)?1:0;
    cout<<endl;
}
void map_strint_bin()
{
    cout<<output<<"map_intdouble_bin"<<output<<endl;
    map<string, int> mymap1 = {{"A" , 1} , {"B" , 2} , {"C" , 3}};
    map<string , int> mymap2;
    binary::serialize_bin(mymap1 , "bin_data\\map_strint.data");
    binary::deserialize_bin(mymap2 , "bin_data\\map_strint.data");
    for(auto iter1 = mymap1.begin() , iter2 = mymap2.begin();iter1!=mymap1.end();iter1++,iter2++)
    {
        cout<<" map1: "<<(*iter1).first<<"  "<<(*iter1).second;
        cout<<" map2: "<<(*iter2).first<<"  "<<(*iter2).second<<endl;
    }
    cout<<endl<<"(mymap1==mymap2)?1:0 Then output:"<<(mymap1==mymap2)?1:0;
    cout<<endl;
}
void map_strstr_bin()
{
    cout<<output<<"map_intdouble_bin"<<output<<endl;
    map<string, string> mymap1 = {{"A" , "a"} , {"B" , "b"} , {"C" , "c"}};
    map<string , string> mymap2;
    binary::serialize_bin(mymap1 , "bin_data\\map_strstr.data");
    binary::deserialize_bin(mymap2 , "bin_data\\map_strstr.data");
    for(auto iter1 = mymap1.begin() , iter2 = mymap2.begin();iter1!=mymap1.end();iter1++,iter2++)
    {
        cout<<" map1: "<<(*iter1).first<<"  "<<(*iter1).second;
        cout<<" map2: "<<(*iter2).first<<"  "<<(*iter2).second<<endl;
    }
    cout<<endl<<"(mymap1==mymap2)?1:0 Then output:"<<(mymap1==mymap2)?1:0;
    cout<<endl;
}

// void base64_help(string filename)
// {
//     fstream file;
//     file.open(filename , ios::in | ios::binary);
//     if(!file.is_open())
//     {
//         cout<<"We can't open this file"<<endl;
//         return ;
//     }
//     string tar;
//     file.read(reinterpret_cast<char*>(&tar), sizeof(tar));
//     cout<<tar<<endl;
//     string result = base64_encode(tar);
//     cout<<"The result of encode :"<<result<<endl;
//     file.close();
//     cout<<"Now we will decode:"<<endl;
//     string de_result = base64_decode(result);
//     cout<<de_result<<endl;
// }

// void test_base64()
// {
//     cout<<"We have accomplish xml , please input :"<<endl;
    
//     cout<<"1.encode     other_input.exit"<<endl;
//     unsigned char help ;
//     cin>>help;
//     while(help=='1')
//     {
//         cout<<"please input the filename : "<<endl;
//         string name;
//         cin>>name;
//         base64_help(name);
//         cout<<"We have accomplish this , please input :"<<endl;
//         cout<<"1.encode     other.exit"<<endl;
//         cin>>help;
//     }
// }