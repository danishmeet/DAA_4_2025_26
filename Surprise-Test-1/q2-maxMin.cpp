int maxMin(int k, vector<int> arr) {
    sort(arr.begin(), arr.end());
    int min_result = INT_MAX;
    for (int i = 0; i <= (int)arr.size()-k; i++) {
        int result = arr[i+k-1]-arr[i];
        if (result < min_result) {
            min_result = result;
        }
    }
    return min_result;
}
