# 1932F -Feed Cats
```c++
#include<bits/stdc++.h>
using namespace std;
int t,n,m,l,r,add[1000005],rem[1000005],from[1000005],f[1000005];
void work(){
	cin>>n>>m;
	for(int i=1;i<=n+1;i++)add[i]=0,rem[i]=0,from[i]=i,f[i]=0;
	for(int i=1;i<=m;i++)cin>>l>>r,add[l]++,rem[r]++,from[r]=min(from[r],l);
	for(int i=n;i>=1;i--)from[i]=min(from[i],from[i+1]);
	f[0]=0;
	int seg=0;
	for(int i=1;i<=n;i++)seg+=add[i],f[i]=max(f[i-1],f[from[i]-1]+seg),seg-=rem[i];
	cout<<f[n]<<endl;
}
int main(){
	cin>>t;
	while(t--)work();
}
```
```c++
//MY ans
#include<iostream>
#define MAXN 1000005
using namespace std ;

class solution
{
private:
    int left[MAXN] , right[MAXN] ,from[MAXN] ,dp[MAXN] ;
public:
    void solve()
    {
        int n , m ;
        cin >> n >> m ;
        for(int i = 1 ; i<= n+1 ;i++)
        {
            left[i] = 0;
            right[i] = 0;
            dp[i] = 0;
            from[i] = i ;
        }
        for(int i = 1 ; i <= m ;i++)
        {
            int tl , tr ;
            cin >> tl >> tr ;
            left[tl] ++;
            right[tr] ++;
            from[tr] = min(from[tr] , tl);
        }
        for(int i = n; i >=1 ;i--)
        {
            from[i] = min(from[i] , from[i+1]);
        }
        dp[0] = 0;
        int temp  = 0 ;
        for( int i = 1  ;i <= n; i++)
        {
            temp += left[i];
            dp[i] = max(dp[i-1] , dp[from[i]-1]+ temp) ;
            temp -= right[i];
        }
        cout << dp[n] <<endl;
    }
};

int main()
{
    int n ;
    cin >> n ;
    solution AC ;
    for(int i = 0 ;i < n ; i++)
    {
        AC.solve();
    }
    return 0;
}
```

# D. Exam in MAC