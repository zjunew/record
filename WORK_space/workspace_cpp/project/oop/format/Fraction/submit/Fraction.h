#ifndef _FRACTION_H
#define _FRACTION_H

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Fraction
{
private:

    int numerator;
    int denominator;
public:

    Fraction();
    Fraction(int a,int b);
    Fraction(const Fraction & tar);
    Fraction(double input);
    Fraction(string s);

    int gcd(int a, int b);
    int pow(int a , int b);
    void function(string s);

    Fraction operator+ (const Fraction & next);
    Fraction operator- (const Fraction & next);
    Fraction operator* (const Fraction & next);
    Fraction operator/ (const Fraction & next);

    int operator> (const Fraction & next);
    int operator>= (const Fraction & next);
    int operator< (const Fraction & next);
    int operator<= (const Fraction & next);
    int operator!= (const Fraction & next);
    int operator== (const Fraction & next);

    double change_double();
    string change_string();
    Fraction simply(int num , int denum);
    void print();
    
};
void test_one();

#endif