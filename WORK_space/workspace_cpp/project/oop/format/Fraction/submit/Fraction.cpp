#include "Fraction.h"

double Fraction::change_double()
{
    double num = numerator , denum = denominator;
    return num / denum;
}
string Fraction::change_string()
{
    return to_string(numerator) + " / " + to_string(denominator);
}

int Fraction::pow(int a , int b)
{
    int result = 1;
    for(int i = 0 ;i < b ; i++)
    {
        result *= a; 
    }
    return result ;
}


void Fraction::function(string s)
{
    int length = s .size() , count = 0 ,choice ;
    string fir , sec ;
    static int flag = 1;
    for(auto x : s )
    { 
        
        if(x == '.')
        {
            choice = 1;
            flag = 0;
            continue;
        }
        if(x == '/')
        {
            choice = 2;
            flag = 0;
            continue;
        }
        if( flag )
        {
            count++;
            fir += x;
        }
        else
        {
            sec += x;
        }
    }
    //cout<<fir<<"     " << sec<<"  "<<help<<"  "<<count<<endl ;
    flag = 1;
    if(choice == 1)
    {
        int b = pow (10,length - count -1) ;
        int a = b* ( stoi(fir) ) +stoi(sec);
        int g = gcd(a,b);
        numerator = a/g ;
        denominator = b/g; 
    }
    else
    {
        int a = stoi(fir);
        int b = stoi(sec);
        int g = gcd(a,b);
        numerator = a/g ;
        denominator = b/g; 
    }
}

Fraction::Fraction(string s)
{
    Fraction::function( s ) ;
}

Fraction::Fraction(double input)
{
    string str = to_string( input );
    Fraction::function( str ) ;
}

Fraction::Fraction(int a,int b)
{
    numerator = a ;
    denominator = b ;
    if(b == 0 )
    {
        cout<<"Wrong input ! Please input again.The denominator can't be 0."<<endl;
    }
}

int Fraction::gcd(int a, int b)
{
    if(b == 0)
    {
        return a;
    }
    return Fraction::gcd(b , a % b);
}

Fraction Fraction::operator+ (const Fraction & next)
{
    int num = numerator * next . denominator + denominator * next.numerator;
    int denum = denominator * next.denominator; 
    return Fraction::simply(num , denum );
}

Fraction Fraction::operator- (const Fraction & next)
{
    int num = numerator * next . denominator - denominator * next.numerator;
    int denum = denominator * next.denominator; 
    return Fraction::simply(num , denum );
}

Fraction Fraction::operator/ (const Fraction & next)
{
    int num = numerator * next .denominator ;
    int denum = denominator * next .numerator ;
    return Fraction::simply(num , denum );
}

Fraction Fraction::operator* (const Fraction & next)
{
    int num = numerator * next.numerator ;
    int denum = next.denominator * denominator ;
    return Fraction::simply(num , denum );
}

Fraction Fraction::simply(int num , int denum)
{
    if(num == 0 )
    {
        return {0 , 0} ;
    }
    int divisor = gcd(abs(num) , abs(denum) ) ;
    return {num / divisor , denum / divisor};
}

Fraction::Fraction(const Fraction & tar)
{
    numerator = tar .numerator ;
    denominator = tar.denominator;
    cout<<"copy constructor is called" <<endl ;
}

void Fraction::print()
{
    cout<<"The answer is: "<<numerator << " / " <<denominator <<endl;
}

int Fraction::operator> (const Fraction & next)
{
    return ( numerator * next . denominator - denominator * next.numerator ) > 0? 1 :0 ;
}
int Fraction::operator>= (const Fraction & next)
{
    return ( numerator * next . denominator - denominator * next.numerator ) >= 0? 1 :0 ;
}
int Fraction::operator< (const Fraction & next)
{
    return ( numerator * next . denominator - denominator * next.numerator ) < 0? 1 :0 ;
}
int Fraction::operator<= (const Fraction & next)
{
    return ( numerator * next . denominator - denominator * next.numerator ) <= 0? 1 :0 ;
}
int Fraction::operator!= (const Fraction & next)
{
    return !( (numerator == next . numerator) && (denominator == next . denominator) );
}
int Fraction::operator== (const Fraction & next)
{
    return (numerator == next . numerator) && (denominator == next . denominator);
}
void test_one()
{
    Fraction m(1.414);
    m.print();
    cout<<endl<<"Conversion from a finite decimal string like: 1.414"<<endl;
    Fraction n("1.414");
    n.print();
}
