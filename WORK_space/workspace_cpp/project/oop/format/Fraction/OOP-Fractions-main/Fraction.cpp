#include "Fraction.h" //Acsess to the header file
#include <iostream>		//Acsess to Cout and Cin
#include <Windows.h>	//Acsess to Sleep()


//All Functions 
Fraction operator*(unsigned int nb, const Fraction& right) /*operator is overloaded here*/
{
	return Fraction(nb*right.Numa, nb * right.Denom);}

//Function to Display Every Object
void FractionList::DisplayList() { 
	//Using a loop and a counter i, cycle through function .DisplayInfo//
	int N{}, D{}, i = 0;
	while (i < List.size()) {cout << "[" << i << "]" << " ";List[i].DisplayInfo(N, D);	i++;}} 

//Return Individual Values of each stored element of fractions()
void FractionList::ReturnIndieVal() {
	//Using a loop and a counter i, cycle through function .DisplayIndie//
	cout << "List has " << List.size() * 2 << " elements in" << endl;
	for (unsigned int i = 0; List.size() > i; i++)
		List[i].DisplayIndie();}

//Modify Individual Terms of the fractions()
int FractionList::ModifyIndieVals(int Selection) {

	Fraction WholeNumber;
	int N, D, Nnew, Dnew, choice = 0, provided=0;
	char reply;
	
		N = List[Selection].getN();		D = List[Selection].getD(); //Collecting and assigning terms 
		cout << "Fraction Choice: [" << Selection << "] " << N << "/" << D << endl;//User Friendliness
		cout << "\n";

		while (provided == 0) { //Condition to make sure the correct input is used
		cout << "N or D" << endl;
		cin >> reply;

		if (reply == 'N') { //Case if Numerator is to be changed
			cout << "Replace: " << N << "    With? "; cin >> Nnew;
			WholeNumber.setN(Nnew);//Set Numarator as the new Vairable
			WholeNumber.setD(D);
			List.push_back(WholeNumber);//Does not replace selection, only adds to list  //FIX//
			WholeNumber.DisplayInfo(Nnew, D); //display the New fraction
			provided++;
		}
		else if (reply == 'D'){//Case if Denominator is to be changed
			cout << "Replace: " << D << "    With? "; cin >> Dnew;
			WholeNumber.setD(Dnew);//Set Denominator as the new Vairable
			WholeNumber.setN(N);
			List.push_back(WholeNumber);
			WholeNumber.DisplayInfo(N, Dnew);//display the New fraction
			provided++; 
		}
		else  {cout << "Please Enter appropiate response" << endl;}; //Response if wrong response is inputted
	}
		return 0;
};

//find the Lowest Terms of the fraction
void FractionList::LT(int N, int D) { //Return Lowest Term 
	FractionList Reduce;
	int LCM;

	LCM = Reduce.ReduceFraction(N, D);//Call function for Lowest Common Multiple 

	//cout << "LCM: " << LCM << " N:" << N << " D: " << D << endl; //Testing
	N /= LCM;	D /= LCM; // Same as N = N/LCM

	//A continjency incase the polaritoes are mixed up. eg, 9/-2
	if (D < 0) { D = D * -1 ; N = -N; cout << N << "/" << D << endl; }

	//Continjency if the denominator is 1. eg 8/1
	else if (D == 1) { cout << N << endl; }

	//Continjency for ever other outcome
	else if (D > 0) { cout << N << "/" << D << endl; }
				
};

//Reduce the fraction into its Lowest Terms
double  FractionList::ReduceFraction(int N, int  D) {//Lowest common multiple
	//Repeat untill D = 0 so that the LCM can be found

	if (D != 0) { return ReduceFraction(D, N % D); }//If D !=0, repeat process but input remainder of N/D in
	else { return N; }//if denominator(D) is Equal = 0, return Numerator(N)

}

//Maths to return correct Mixed Fraction
int FractionList::Mixed(int N, int D) {
	FractionList Reduce;

	int Whole{}, Remainder{}, LCM{}, Nnew{};
	Whole = N / D; //Whole number
	Remainder = N % D; //Remainder

	LCM = Reduce.ReduceFraction(Remainder, D);//Pass Remainder and Denom into reduce fraction to find LDM

	Nnew = Remainder / LCM; //Finding Numa by reducing the remainder by LCM
	D /= LCM;


	//Contingencies so that all fractions work correctly
	if (D < 0) {D = -D;	cout << Whole << " " << Nnew << "/" << D << endl;}
	else if (Nnew == 0) {cout << Whole << endl;	}
	else if (Nnew < 0) {Nnew = -Nnew;cout << Whole << " " << Nnew << "/" << D << endl;}
	else if (Whole == 0) {cout << Nnew << "/" << D << endl;}
	else { cout << Whole << " " << Nnew << "/" << D << endl; }
	return 0;
}

//Maths to return correct Real value
double FractionList::Real(double N, double D) {
	//Double, along with the Decimal means for a more accurate awnser
	double R = 0.0;
	R = N / D; 
	cout << R; //Print 'R' 
	return 0;
}


//Function collecting all forms of fraction
void FractionList::ALL() {

	FractionList ALL;
	Fraction Cal2;
	int N{}, D{};

	cout << "\n" << "All Fraction in the text file in their 5 forms" << endl << "\n";

	for (int i = 0; i < List.size(); i++) { //Loops through index i
		N = List[i].getN();	D = List[i].getD(); //Get N and D based off i
		
			cout << "Fraction: "<< "["<< i << "]" << endl;
			cout << "Inital Form: "; List[i].DisplayInfo(N, D); 
			cout << "Reduced Term: "; ALL.LT(N,D);
			cout << "Mixed Form: "; ALL.Mixed(N, D);
			cout << "Real Numbers: "; ALL.Real(N, D);
			cout << "\n";
			cout << "******************" << endl;

			Sleep(500);//Delay so its eaiser on the eyes, not bombarded with text
	}
}

//Opens file and saves all numbers into their own objects inside a vector
unsigned int FractionList::GetListFromFile(string FileName) {
	ifstream FractionFile(FileName);
	if (!FractionFile.fail()) {
		string Numa, Denom;
		Fraction WholeFraction;

		//As the file reads the numarator/denominator as strings
		while (FractionFile >> Numa >> Denom)

			//These values are converted into doubles and passsed thorugh to their respective function for storing
		{
			WholeFraction.setN(stod(Numa)); WholeFraction.setD(stod(Denom));

			//Add object 'WholeFraction' to the vector list
			List.push_back(WholeFraction);
		}
	}

	//Incase the file does not open correctly there will be a message to let the user know
	else { cout << "File did not open" << endl; }

	return 0;
};






//Attempt at sum of all fraction
int FractionList::ADDALL() {//-83 //1330560   //Looking for 43/5

	int n1{}, d1{}, Tn=0, Td = 1, n, d;
		
	FractionList Sum;

	for (int i = 0; i < List.size(); i++) {
		
		n1 = List[i].getN(); 	
		d1 = List[i].getD();		
		//cout << "N1: " << n1 <<endl;
		//cout << "D1: " << d1<< endl;

		Td = Td * d1;//Denominator works

		Tn = Tn + n1 * (Td/d1);

		//10/4 + 20/3 = 3*10+20*4/4*3
		//n1/d1 + n2/d2 = (d2*n1)+(n2*d1)/(d1*d2)
		//n1/d1 + 
		// 
		//Td = Td * d1;

		cout << Tn << "/" << Td << endl; 
	}
	cout << "Inital Form: "<< Tn << "/" << Td << endl;
	cout << "Reduced Term: "; Sum.LT(Tn,Td);
	cout << "Mixed Form: "; Sum.Mixed(Tn, Td);
	cout << "Real Numbers: "; Sum.Real(Tn, Td);
	cout << "\n";
		 	
	return 0;
}

//Attempt at resulting fraction
void Fraction::ResultingFraction(int n,int d) {
	//ResultingFraction = F6 - ((F1 + F2) * F3 - F4) / F5;

	//Fraction F1, F2,tot;
	cout << "\n";
	cout << "Fraction: ";
	cout << n << "/" << d << endl;	
	//n2 = List[1].getN();
	//d2 = List[1].getD();
	//List[i].DisplayInfo(n, d);
	
}

//Another Attempt at sum of all fraction
int FractionList::Q4() {
	int i{},n{},d{};
	Fraction F6, F5, F4, F3, F2, F1, F0;
	cout << "List Size"<<List.size() << endl;;

	while (i < List.size()) {

		for (int i = 0; i < 8; i++); {
			
			n = List[i].getN();
			d = List[i].getD();
			//List[i].DisplayIndie();

			//cout << i << endl;
			if (i == 6) { cout << "I = " << i << " "; F6.ResultingFraction(n, d); }
			else if (i == 5) { cout << "I = " << i << " "; F5.ResultingFraction(n, d); }
			else if (i == 4) { cout << "I = " << i << " "; F4.ResultingFraction(n, d); }
			else if (i == 3) { cout << "I = " << i << " "; F3.ResultingFraction(n, d); }
			else if (i == 2) { cout << "I = " << i << " "; F2.ResultingFraction(n, d); }
			else if (i == 1) { cout << "I = " << i << " "; F1.ResultingFraction(n, d); }
			else { F0.ResultingFraction(n, d); };

			
			
			//cout << "Loop is still going" << endl;
			
		};
		i++;
	}

	cout << "Loop has finished" << endl;
	return 0;
}