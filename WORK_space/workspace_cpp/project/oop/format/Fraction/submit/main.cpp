#include "Fraction.h"


int main()
{
    cout<<"Default ctor | Ctor takes two integers as parameters | Copy ctor"<<endl;
    //initiation
    Fraction a(1,2);//2个整数输入
    Fraction b(3,5);
    Fraction c(1, 0);//不合法的输入
    //拷贝构造
    Fraction e(a);
    e.print();
    Fraction d = b ;
    d.print();
    
    //double 和string 类的测试
    // Fraction m(1.414);
    // m.print();
    // cout<<endl<<"Conversion from a finite decimal string like: 1.414"<<endl;
    // Fraction n("1.414");
    // n.print();
    test_one();

    cout<<endl<<"All kinds of Arithmetical operators:"<<endl;
    //All kinds of Arithmetical operators
    Fraction plus = a + b ;
    plus.print();
    Fraction de = a - b ;
    de.print();
    Fraction mul = a * b ;
    mul.print();
    Fraction div = a / b ;
    div.print();

    //Relational operators: < <= == != >= >
    cout<<endl<<"Relational operators: < <= == != >= >"<<endl;

    cout<<"a <= b : " << (a <= b)<<endl;
    cout<<"a < b : " << (a < b) <<endl;
    cout<<"a >= b : " << (a >= b) <<endl;
    cout<<"a > b : " << (a > b) <<endl;
    cout<<"a == b : " << (a == b) <<endl;
    cout<<"a != b : " << (a != b) <<endl;


    //类型转换
    cout<<endl<<"Typecast to double | To string"<<endl;
    double k = a.change_double();
    cout<<" k = " <<k <<endl;

    string s = a.change_string( ) ;
    cout << "s = " << s <<endl;

    cout<<endl<< "Inserter and extractor for streams"<< endl;

    cout<<"Please input a fraction number like 2/3 : "<<endl;
    string fr ;
    cin >> fr ;
    Fraction stream(fr);
    stream.print();

    system("pause");
    return 0 ;
}