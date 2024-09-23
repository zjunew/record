#include"book.h"
void book::read()
{
    ifstream re("diary.txt");
    string data ;
    getline(re,data);
    while(data==start)
    {
        string time ;
        getline(re , time) ;
        
        vector<string> tempt;
        while(data != end)
        {
            getline(re , data) ;
            tempt.push_back(data);
        }
        diary_book.emplace(pair<string,vector<string>>(time,tempt));
        getline(re,data);
    }
}

vector<string> book::get_text()
{
    
    vector<string> text;
    string s;
    
    
    while(getline(cin , s ) && s[s.size()-1]!='.')
    {
        text.push_back(s);
        //getline(cin , s );
    }
    text.push_back(s);
    text.push_back(end);
    return text;
}

void book::write()
{
    ofstream wr("diary.txt");

    for(auto [x,y] : diary_book)
    {
        wr<<start<<endl;
        wr<<x<<endl;
        for(auto m:y)
        {
            wr<<m<<endl;;
        }
        
    }
    wr.close();
}
void book::data_sort(vector<string>& data)
{
    int size = data.size();
    for(int i = 0 ; i< size -1 ;i++)
    {
        for(int j = 0 ; j < size -1 -i ;j++)
        {
            if(data[j] > data[j+1])
            {
                auto temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}





