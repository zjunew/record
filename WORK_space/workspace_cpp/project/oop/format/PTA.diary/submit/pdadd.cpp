#include"book.h"

int main()
{
    
    string time ,command; 
    cout<<"please input time ,for example : 2024-04-13"<<endl;
    
    book diary;
    getline(cin  , time);
    
    diary.read();
    diary.write();
    if(diary.diary_book.count(time))
    {
        vector<string> temp = diary.get_text();
        diary.diary_book[time] = temp ;
    }
    else 
    {
        vector<string> temp = diary.get_text();
        diary.diary_book.emplace(pair<string,vector<string>>(time,temp));
    }
    diary.write();
    cout<<"We have accomplished this diary." <<endl;
    
    system("pause");
    return 0;
}