#include "Vector.h"

void test_int();
void test_double();
void test_float();
void test_at_one();
void test_at_two();
void input();

int main()
{
    // const string s = "------------------This is a new test--------------------";
    // Vector<int> test1 ;
    // test1.push_back(1);
    // test1.push_back(100);
    // cout<< test1.size() <<"  "<<test1[1]<<endl;
    input();
    int choice ; 
    cin >> choice ;
    while(choice)
    {
        switch (choice)
        {
        case 1:
            test_int();
            break;
        
        case 2:
            test_double();
            break;

        case 3:
            test_float();
            break;
        
        case 4:
            test_at_one();
            break;
        
        case 5:
            test_at_two();
            break;
        }
        cout<<"Please input  0:Exit     1:int    2:double    3:float     4:test at(index)index<0     5:test at(index)index>m_nSize"<<endl;
        cin >> choice ;
    }
    system("pause");
    //Vector<int>a;
}

void input()
{
    cout<<"We will test all the facilities of the class Vector."<<endl;
    cout<<"tips:when we use Vector() ,it will show 'Vector()'."<<endl;
    cout<<"    when we use ~Vector() ,it will show '~Vector()'."<<endl;
    cout<<"    when we use Vector(int size) ,it will show 'Vector(int size)'."<<endl;
    cout<<"    when we use Vector(const Vector& r) ,it will show 'Vector(const Vector& r)'."<<endl;
    cout<<"Please input a nuber :"<<endl;
    cout<<"0:Exit     1:int    2:double    3.float     4.test at(index)index<0     5.test at(index)index>m_nSize"<<endl;
}

void test_int()
{
    cout<<"------------------This is a new test about int--------------------"<<endl;
    Vector<int> test ;
    for(int i = 0 ; i < 20 ; i++)
    {
        test.push_back(i);
    }
    cout<<"Now we will test size():"<<endl;
    cout<< test.size()<<endl;
    cout<<"Now we will test at() and [] ,which also proves that push_back() is useful"<<endl;
    for(int i = 0 ; i < 20 ; i+=2)
    {
        cout<<"test[]:"<<test[i]<<" at():"<<test.at(i+1)<<" "; 
    }

    cout<<endl<<"Now we will test Vector(int size): "<<endl;
    Vector<int> test1(20);
    cout<<"Now we will test size():"<<endl;
    cout<<test1.size()<<endl;

    cout<<"Now we will test Vector(const Vector& r): "<<endl;
    Vector<int> test2(test);
    cout<<"Now we will test at() and [] ,which also proves that push_back() is useful"<<endl;
    for(int i = 0 ; i < 20 ; i+=2)
    {
        cout<<"test[]:"<<test2[i]<<" at():"<<test2.at(i+1)<<" "; 
    }
    cout<<endl<<"Now we will test bool empty() const: "<<endl;
    cout<<test2.empty()<<endl;

    cout<<"Now we will test void clear(): we will use empty to identify "<<endl;
    test2.clear();
    cout<<test2.empty()<<endl;

    //cout<<"function:when index <0 or >=m_nSize  "<<test.at(20)<<endl;;
}

void test_double()
{
    cout<<"------------------This is a new test about double--------------------"<<endl;
    Vector<double> test ;
    for(int i = 0 ; i < 20 ; i++)
    {
        test.push_back(i);
    }
    cout<<"Now we will test size():"<<endl;
    cout<< test.size()<<endl;
    cout<<"Now we will test at() and [] ,which also proves that push_back() is useful"<<endl;
    for(int i = 0 ; i < 20 ; i+=2)
    {
        cout<<"test[]:"<<test[i]<<" at():"<<test.at(i+1)<<" "; 
    }

    cout<<endl<<"Now we will test Vector(int size): "<<endl;
    Vector<double> test1(20);
    cout<<"Now we will test size():"<<endl;
    cout<<test1.size()<<endl;

    cout<<"Now we will test Vector(const Vector& r): "<<endl;
    Vector<double> test2(test);
    cout<<"Now we will test at() and [] ,which also proves that push_back() is useful"<<endl;
    for(int i = 0 ; i < 20 ; i+=2)
    {
        cout<<"test[]:"<<test2[i]<<" at():"<<test2.at(i+1)<<" "; 
    }
    cout<<endl<<"Now we will test bool empty() const: "<<endl;
    cout<<test2.empty()<<endl;

    cout<<"Now we will test void clear(): we will use empty to identify "<<endl;
    cout<<"void clear(): "<<endl;
    test2.clear();
    cout<<test2.empty()<<endl;

    //cout<<"function:when index <0 or >=m_nSize  "<<test.at(20)<<endl;;
}

void test_float()
{
    cout<<"------------------This is a new test about float--------------------"<<endl;
    Vector<float> test ;
    for(int i = 0 ; i < 20 ; i++)
    {
        test.push_back(i);
    }
    cout<<"Now we will test size():"<<endl;
    cout<< test.size()<<endl;
    cout<<"Now we will test at() and [] ,which also proves that push_back() is useful"<<endl;
    for(int i = 0 ; i < 20 ; i+=2)
    {
        cout<<"test[]:"<<test[i]<<" at():"<<test.at(i+1)<<" "; 
    }

    cout<<endl<<"Now we will test Vector(int size): "<<endl;
    Vector<float> test1(20);
    cout<<"Now we will test size():"<<endl;
    cout<<test1.size()<<endl;

    cout<<"Now we will test Vector(const Vector& r): "<<endl;
    Vector<float> test2(test);
    cout<<"Now we will test at() and [] ,which also proves that push_back() is useful"<<endl;
    for(int i = 0 ; i < 20 ; i+=2)
    {
        cout<<"test[]:"<<test2[i]<<" at():"<<test2.at(i+1)<<" "; 
    }
    cout<<endl<<"Now we will test bool empty() const: "<<endl;
    cout<<test2.empty()<<endl;

    cout<<"Now we will test void clear(): we will use empty to identify"<<endl;
    test2.clear();
    cout<<test2.empty()<<endl;

    //cout<<"function:when index <0 or >=m_nSize  "<<test.at(20)<<endl;;
}

void test_at_one()
{
    cout<<"------------------This is a new test 4--------------------"<<endl;
    Vector<int> test1;
    test1.push_back(1);
    cout<<"correct index: "<<test1.at(0)<<endl;
    cout<<"error index : index <0"<<endl;
    test1.at(-1);
}

void test_at_two()
{
    cout<<"------------------This is a new test 5--------------------"<<endl;
    Vector<int> test1;
    test1.push_back(1);
    cout<<"correct index: "<<test1.at(0)<<endl;
    cout<<"error index : index >= m_nSize "<<endl;
    test1.at(2);
}