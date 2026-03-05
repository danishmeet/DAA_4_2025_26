#include <bits/stdc++.h>
using namespace std;

int subset(vector<int> &arr, int targetSum, int n){
    if(targetSum == 0){
        return 1;
    }
    if(n == 0 || targetSum < 0){
        return 0;
    }
    int include = subset(arr, targetSum-arr[n-1], n-1);
    int exclude = subset(arr, targetSum, n-1);
    return include + exclude;
}

int main() {
    vector<int> arr = {1,2,3};
    int targetSum = 3;
    int n = arr.size();
    cout << subset(arr, targetSum, n);
    return 0;
}