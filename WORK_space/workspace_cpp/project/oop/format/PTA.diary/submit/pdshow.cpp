#include"book.h"

int main()
{
    book diary;
    diary.read();
    string s;
    cout<<"please input the data"<<endl;
    getline(cin , s) ;
    if(diary.diary_book.count(s))
    {
        cout<<diary.start<<endl;
        cout<<s<<endl;
        for(auto x:diary.diary_book[s])
        {
            cout<< x <<endl;
        }
    }
    else
    {
        cout<<"Can't find this data, please input again.";
    }
    system("pause");
    return 0;
}