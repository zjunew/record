```c++
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<regex>
#include<algorithm>
using namespace std ;



class book 
{
public:
    void pdadd();
    void pdlist();
    void pdremove();
    void pdshow();
    void write();
    void data_sort(vector<string>& data);
    vector<string> get_text();
    void read();
private:
    const string start="---------------------     NEW PAGE.  This is the data:  -----------------------";
    const string end = "---------------------     End of this diary.            -----------------------";
    unordered_map<string,vector<string>> diary_book;
};

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
    cout<<"Now, we have accomplished this diary."<<endl;
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
void book::pdadd()
{
    
    string time ; 
    cout<<"please input time ,for example : 2024-04-13"<<endl;
    getline(cin  , time);
    
    read();

    if(diary_book.count(time))
    {
        vector<string> temp = get_text();
        diary_book[time] = temp ;
    }
    else 
    {
        vector<string> temp = get_text();
        diary_book.emplace(pair<string,vector<string>>(time,temp));
    }
    write();
}

void book::pdlist()
{
    vector<string> sort_data;
    read();
    for(auto it = diary_book.begin() ; it != diary_book.end() ; it++ )
    {
        sort_data.push_back(it->first);
    }
    data_sort(sort_data);
    for(auto x : sort_data)
    {
        cout<<start<<endl;
        cout<<x<<endl;
        for(auto m:diary_book[x])
        {
            cout<<m<<endl;;
        }
    }
}
//pdremove删除一个日期实体。成功时返回0，失败时返回-1。
void book::pdremove()
{
    read();
    string s;
    cout<<"please input the data"<<endl;
    getline(cin , s) ;
    if(diary_book.count(s))
    {
        diary_book.erase(s);
        cout<<"we have remove it!"<<endl;;
        write();
    }
    else
    {
        cout<<"Can't find this data, please input again."<<endl;
    }
}

void book::pdshow()
{
    read();
    string s;
    cout<<"please input the data";
    getline(cin , s) ;
    if(diary_book.count(s))
    {
        cout<<start<<endl;
        cout<<s<<endl;
        for(auto x: diary_book[s])
        {
            cout<< x <<endl;
        }
    }
    else
    {
        cout<<"Can't find this data, please input again.";
    }
}

void print_start()
{
    cout<<"-------------     pdadd     , please input it     ---------------"<<endl;
    cout<<"-------------     pdlist    , please input it     ---------------"<<endl;
    cout<<"-------------     pdremove  , please input it     ---------------"<<endl;
    cout<<"-------------     pdshow    , please input it     ---------------"<<endl;
}
void print_start_one()
{
    cout<<"-------------          DIARY BOOK                 ---------------"<<endl;
    cout<<"-------------     pdadd     , please input it     ---------------"<<endl;
    cout<<"-------------     pdlist    , please input it     ---------------"<<endl;
    cout<<"-------------     pdremove  , please input it     ---------------"<<endl;
    cout<<"-------------     pdshow    , please input it     ---------------"<<endl;
}
void choose_write()
{
    print_start_one();
    book mydiary;
    string command;
    getline(cin  , command);
    while(command!="END")
    {
        
        if(command == "pdadd")
            mydiary.pdadd();
        else if(command == "pdlist")
            mydiary.pdlist();
        else if(command == "pdremove")
            mydiary.pdremove();
        else if(command == "pdshow")
            mydiary.pdshow();
        else
            cout<<"Can't find the command , please input again."<<endl
            <<"If you want to stop, please input 'END'"<<endl;
        print_start();
        getline(cin  , command);
    }
    system("pause");
}
int main()
{
    choose_write();
    return 0;
}
```