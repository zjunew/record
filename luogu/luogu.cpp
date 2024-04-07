#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// Function to compare two integers
int cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}

int main() {    
    int n, v;
    cin >> n >> v;
    vector<pair<int, int>> items; // Pair of weight and value of items
    
    // Inputting weights and values of items
    for(int i = 0; i < n; i++) {
        int weight, value;
        cin >> weight >> value;
        items.push_back(make_pair(weight, value));
    }
    
    // Sorting items in non-increasing order of value
    sort(items.begin(), items.end(), cmp);
    
    int totalValue = 0;
    vector<int> selectedItems;
    
    // Selecting items based on their weight and truck capacity
    for(auto& item : items) {
        if(v >= item.first) {
            selectedItems.push_back(item.first);
            totalValue += item.second;
            v -= item.first;
        }
    }
    
    // Output the maximum total value
    cout << totalValue << endl;
    
    // Output the item numbers that make the optimal set
    for(int i = 0; i < n; i++) {
        if(selectedItems.size() > 0 && items[i].first == selectedItems.back()) {
            cout << i + 2 << " ";
            selectedItems.pop_back();
        }
    }
}
