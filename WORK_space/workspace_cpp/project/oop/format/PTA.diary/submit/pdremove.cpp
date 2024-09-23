#include"book.h"

int main()
{
    book diary;
    string com;

    diary.read();
    string s;
    cout<<"please input the data"<<endl;
    getline(cin , s) ;
    if(diary.diary_book.count(s))
    {
        diary.diary_book.erase(s);
        cout<<"we have remove it!"<<endl;;
        diary.write();
    }
    else
    {
        cout<<"Can't find this data, please input again."<<endl;
    }
    
    system("pause");
    return 0;
}