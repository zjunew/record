#include <bits/stdc++.h>
int T,a,b,c;
int main() {
    std::cin>>T;
    while(T--){
        std::cin>>a>>b>>c;
        std::cout<<(a+1!=c?-1:b/c+ceil(log2(c+b%c)))<<'\n';
    }
    return 0;
}