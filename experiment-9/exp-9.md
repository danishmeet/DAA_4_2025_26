# Experiment 9 - Minimum Sum Partition

## Problem Statement

Given an array of `n` positive integers, partition the array into two subsets such that the absolute difference between the sum of elements in both subsets is minimized.

Divide the array into two groups **S1** and **S2** such that `|sum(S1) − sum(S2)|` is minimum.

**GFG Link:** [Minimum Sum Partition](https://www.geeksforgeeks.org/problems/minimum-sum-partition3317/1)

---

## Algorithm

```
1. Compute totalSum = sum of all elements in arr[]
2. Create a DP boolean array dp[0..totalSum] where dp[j] = true
   means a subset with sum j is achievable
3. Initialize dp[0] = true (empty subset has sum 0)
4. For each element in arr[]:
       For j from totalSum down to arr[i]:
           dp[j] = dp[j] OR dp[j - arr[i]]
5. Iterate j from totalSum/2 down to 0:
       If dp[j] is true:
           return totalSum - 2*j   ← minimum difference
```

---

## Code (C++)

```cpp

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

```

---

## Dry Run

**Input:** `n = 4`, `arr = [1, 6, 11, 5]`

**Step 1:** totalSum = 1 + 6 + 11 + 5 = **23**

**Step 2:** Initialize `dp[0..23]` → all `false` except `dp[0] = true`

**Step 3:** Process each element:

| Element | Notable Reachable Sums After Processing     |
|---------|---------------------------------------------|
| 1       | {0, 1}                                      |
| 6       | {0, 1, 6, 7}                                |
| 11      | {0, 1, 6, 7, 11, 12, 17, 18}               |
| 5       | {0, 1, 5, 6, 7, 11, 12, 16, 17, 18, 22, 23}|

**Step 4:** Check from `totalSum/2 = 11` downward:
- `dp[11] = true` → S1 sum = 11, S2 sum = 23 − 11 = 12
- Minimum Difference = |12 − 11| = **1**

**Output:** `1`

---

## Time and Space Complexity

| Metric           | Value       | Explanation                                             |
|------------------|-------------|---------------------------------------------------------|
| Time Complexity  | O(n × sum)  | n elements × totalSum (≤ 100 × 100,000 = 10^7 ops)     |
| Space Complexity | O(sum)      | 1D boolean DP array of size totalSum + 1                |

> Constraints: n ≤ 100, arr[i] ≤ 1000 → max totalSum = 1,00,000

---

## Example

**Input:**
```
1
4
1 6 11 5
```

**Output:**
```
1
```

**Explanation:** Partition into `{1, 5, 6}` (sum = 12) and `{11}` (sum = 11) → |12 − 11| = **1**

---
