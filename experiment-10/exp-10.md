# Experiment 10 - Distinct Subsequences

## Problem Statement

Given two strings `s` and `t`, return the number of distinct subsequences of `s` which equals `t`.

A subsequence is formed by deleting some (or no) characters from the original string without changing the relative order of remaining characters.

**LeetCode Link:** [Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/description/)

---

## Algorithm

```
1. Let m = s.length(), n = t.length()
2. Create a 2D DP array dp[m+1][n+1]
   dp[i][j] = number of ways to form t[0..j-1] using s[0..i-1]
3. Base cases:
     dp[i][0] = 1 for all i  (empty t is a subsequence of any prefix of s)
     dp[0][j] = 0 for j > 0  (non-empty t cannot be formed from empty s)
4. Fill the table:
     For i from 1 to m:
       For j from 1 to n:
         if s[i-1] == t[j-1]:
             dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
                        (use this char) + (skip this char)
         else:
             dp[i][j] = dp[i-1][j]
                        (can only skip this char)
5. Return dp[m][n]
```

---

## Code (C++)

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();

        vector<vector<unsigned long long>> dp(m + 1, vector<unsigned long long>(n + 1, 0));

        for (int i = 0; i <= m; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }

        return (int)dp[m][n];
    }
};
```

---

## Dry Run

**Input:** `s = "rabbbit"`, `t = "rabbit"`  
**m = 7, n = 6**

DP Table (`dp[i][j]`):

|   | "" | r | a | b | b | i | t |
|---|----|---|---|---|---|---|---|
| **""** | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
| **r** | 1 | 1 | 0 | 0 | 0 | 0 | 0 |
| **a** | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
| **b** | 1 | 1 | 1 | 1 | 0 | 0 | 0 |
| **b** | 1 | 1 | 1 | 2 | 1 | 0 | 0 |
| **b** | 1 | 1 | 1 | 3 | 3 | 0 | 0 |
| **i** | 1 | 1 | 1 | 3 | 3 | 3 | 0 |
| **t** | 1 | 1 | 1 | 3 | 3 | 3 | 3 |

**Output:** `dp[7][6] = 3` ✅

---

**Verification with Example 2:** `s = "babgbag"`, `t = "bag"` → **Output: 5** ✅

---

## Time and Space Complexity

| Metric           | Value        | Explanation                                      |
|------------------|--------------|--------------------------------------------------|
| Time Complexity  | O(m × n)     | Fill every cell of the (m+1) × (n+1) DP table   |
| Space Complexity | O(m × n)     | 2D DP array of size (m+1) × (n+1)               |

> Can be optimised to **O(n)** space by using a single 1D DP array iterated right-to-left.

---

## Examples

**Example 1:**
```
Input:  s = "rabbbit", t = "rabbit"
Output: 3
```
There are 3 ways to delete one `b` from `"rabbbit"` to form `"rabbit"`.

**Example 2:**
```
Input:  s = "babgbag", t = "bag"
Output: 5
```

---
