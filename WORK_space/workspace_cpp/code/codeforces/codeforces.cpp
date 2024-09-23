#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std ;
const int  MAXN=2e6+10;

int zero[MAXN] ;
string nums[MAXN] ;

void solve()
{
    int n , m ,sum = 0 ; 
    cin >> n >> m;
    for(int i = 1 ; i <= n ;i++)
    {
        //zero[i] = 0;
        cin>>nums[i] ;
        sum += nums[i].size();
        for(int k = nums[i].size()-1 ; k >= 0 ; k--)
        {
            if(nums[i][k] == '0')
            {
                zero[i] ++ ;
            }
            else
                break;
        }
    }
    sort(zero+1, zero+n+1 );
    for(int i = n ; i >= 1 ;i -= 2 )
        sum -= zero[i];

    if (sum >= m+1) printf("Sasha\n");
	else printf("Anna\n");
    for(int i = 1 ;i <= n ;i++)
        zero[i] = 0;
}

int main()
{
    int n ;
    cin >> n ;
    for(int i = 0 ;i < n ; i++)
    {
        solve();
    }
    return 0;
}
