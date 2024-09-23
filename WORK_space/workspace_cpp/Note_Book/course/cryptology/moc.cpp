#include<iostream>
using namespace std;

int ex_gcd(int a, int b, int &x, int &y) {  // 函数返回gcd(a, b)
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int r = ex_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}
 
int main() {
    int a=7, b=11, x, y;
    //cin >> a >> b;  // 求a关于模b的逆元
    cout << (ex_gcd(a, b, x, y) == 1 ? (x % b + b) % b : -1) << endl;  // -1表示逆元不存在
 
    return 0;
}