#ifndef Fraction_H
#define Fraction_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
//Class's

class Fraction
{
	int Numa, Denom;

public:

	Fraction(int NewNuma=0, int NewDenom=0): Numa(NewNuma), Denom(NewDenom) {}; //Constructor
	inline int getN() const { return Numa; }; //Acsessor Function 
	inline int getD() const { return Denom; };
	inline void setN(const int NewNuma) { Numa = NewNuma; return; }//Set functions / Mutators 
	inline bool setD(const int NewDenom) { bool set = false; if (Denom != 0) set = true; Denom = NewDenom; return set; }//Bool--> (can be Pos or Neg just not 0) //Not sure about this either
	inline void DisplayInfo(int N, int D) { cout << getN() << "/" << getD() << endl; };
	void DisplayIndie() { cout << Numa << ", " << Denom << ", "; };//Not a fan of the final ',' Is a for loop too complex?
	void ResultingFraction(int a, int b);

	Fraction operator+(const Fraction& right) /*operator is overloaded here*/const
	{return Fraction(Numa + right.Numa, Denom +right.Denom);}//Math
	
	Fraction operator-(const Fraction& right) /*operator is overloaded here*/const
	{return Fraction(Numa - right.Numa, Denom - right.Denom);}
		
	friend Fraction operator*(unsigned int nb, const Fraction& right);

	Fraction operator/(const Fraction& right) /*operator is overloaded here*/const
	{return Fraction(Numa / right.Numa, Denom / right.Denom);}
};


class FractionList

{
	vector<Fraction> List;	//vector list is created of the class fraction
public:
	unsigned int GetListFromFile(string FileName);
	void DisplayList(); //Display the list of values 
	void ReturnIndieVal(); //Return individual values
	int ModifyIndieVals(int A);	//Modify specific value
	void LT(int A,int B); //Lowest terms 
	double ReduceFraction(int a, int b); //Reduce the fraction
	int Mixed(int a, int b); //Mixed Fraction
	double Real(double a, double b); //Real Number
	void ALL();


	//Not correctly working functions attempting Q4
	int ADDALL();
	int Q4();
};

#endif