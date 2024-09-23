#include"book.h"

int main()
{
    book diary;
    vector<string> sort_data;
    diary.read();
    for(auto it = diary.diary_book.begin() ; it != diary.diary_book.end() ; it++ )
    {
        sort_data.push_back(it->first);
    }
    diary.data_sort(sort_data);
    for(auto x : sort_data)
    {
        cout<<diary.start<<endl;
        cout<<x<<endl;
        for(auto m:diary.diary_book[x])
        {
            cout<<m<<endl;;
        }
    }
    system("pause");
    return 0;
}