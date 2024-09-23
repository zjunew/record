#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int T,n,m,k[200005];// k数组存储每个数的后导零数量 
string s[200005];//用 string 类型存储每个数 
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&n,&m);
		int sum=0;//用来统计最终数的位数 
		for(int i=1;i<=n;i++) {
			cin>>s[i];
			sum+=s[i].size();//先加上所有数的总位数 
			for(int j=s[i].size()-1;j>=0;j--) {//计算每个数的后导零数量 
				if (s[i][j]=='0') k[i]++;
				else break;
			}
		}
		sort(k+1,k+n+1);//将后导零数量进行排序 
		for(int i=n;i>=1;i-=2) sum-=k[i];//对应 Anna 的每次操作，在 Anna 每次操作后 sum 减少当前后导零数量
		if (sum>=m+1) printf("Sasha\n");//记得是 m+1  
		else printf("Anna\n");
		fill(k+1,k+n+1,0);//多测清空，等价于for(int i=1;i<=n;i++) k[i]=0;
	}
	return 0;//完美结束撒花！！！ 
}