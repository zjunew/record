#include "Fraction.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

int main()
{
	Fraction Object2;
	FractionList Object1; //Object from Fractin List class
	unsigned int FileSize, Selection = 0; //Initaliser to reduce memory
	int D{}, N {};
	
	FileSize = Object1.GetListFromFile("FractionList.txt");

	cout << "Display fractions from file" << endl << "*******************" << endl;
	
	Object1.DisplayList();
	cout << "**************" << endl;
	Object1.ReturnIndieVal();
	cout << "\n";
	cout << "**************" << endl;				//
	cout << "Select a Fraction: "; cin >> Selection;// Comment these put to ignore modify selection
	cout << "**************" << endl;				//
	Object1.ModifyIndieVals(Selection); 
	cout << "**************" << endl;
	Object1.ALL();

	system("pause");
	return 0;
}

