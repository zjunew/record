# 3.17
* 2001. Number of Pairs of Interchangeable Rectangles
You are given n rectangles represented by a 0-indexed 2D integer array rectangles, where rectangles[i] = [widthi, heighti] denotes the width and height of the ith rectangle.

Two rectangles i and j (i < j) are considered interchangeable if they have the same width-to-height ratio. More formally, two rectangles are interchangeable if widthi/heighti == widthj/heightj (using decimal division, not integer division).

Return the number of pairs of interchangeable rectangles in rectangles.

 
```c++
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long interchangeableRectangles(vector<vector<int>>& rectangles) {
    unordered_map<string, int> map;
    for(auto & cur : rectangles) {
        int g = gcd(cur[0], cur[1]);
        string key = to_string(cur[0] / g) + "/" + to_string(cur[1] / g);
        map[key]++;
    }

    long long count = 0;
    for(auto &[key, cur] : map) {
        count += (long long)cur * (cur - 1) / 2;
    }

    return count;
}
```

* 2183. Count Array Pairs Divisible by K
Given a 0-indexed integer array nums of length n and an integer k, return the number of pairs (i, j) such that:

0 <= i < j <= n - 1 and
nums[i] * nums[j] is divisible by k.

>solution:
```c++
class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        vector<int > div ;
        for(int i = 1 ;i * i <= k ; i++ )
        {
            if(k % i == 0)
            {
                div.push_back( i ) ;
                if(i * i < k)
                {
                    div.push_back( k / i ) ;
                }
            }
        }
        unordered_map < int ,int > map ;
        long long ans = 0 ;
        for(auto & v : nums)
        {
            ans += map[ k / gcd(k , v )] ;
            for(auto x : div)
            {
                if( v % x == 0)
                map[x]++ ;
            }
        }
        return ans ;
    }
};
```
