#ifndef BOOK__H
#define BOOK__H
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<algorithm>
using namespace std;


class book 
{
public:
    void write();
    void data_sort(vector<string>& data);
    vector<string> get_text();
    void read();
    unordered_map<string,vector<string>> diary_book;
    const string start="---------------------     NEW PAGE.  This is the data:  -----------------------";
    const string end = "---------------------     End of this diary.            -----------------------";
    
};




#endif