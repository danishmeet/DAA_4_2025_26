class Solution {
  public:
 int minDifference(vector<int>& arr) {
        int n = arr.size();
        int totalSum = 0;
        for (int i = 0; i < n; i++)
            totalSum += arr[i];

        vector<bool> dp(totalSum + 1, false);
        dp[0] = true;

        for (int i = 0; i < n; i++) {
            for (int j = totalSum; j >= arr[i]; j--) {
                dp[j] = dp[j] || dp[j - arr[i]];
            }
        }

        for (int j = totalSum / 2; j >= 0; j--) {
            if (dp[j]) {
                return totalSum - 2 * j;
            }
        }
        return 0;
    }
};