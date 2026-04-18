#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Solution {
  vector<vector<int>> dp;

public:
  int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    dp = vector<vector<int>>(m, vector<int>(n, -1));
    return dfs(0, 0, word1, word2, m, n);
  }
  int dfs(int i, int j, string &word1, string &word2, int m, int n) {
    if (i == m)
      return n - j;
    if (j == n)
      return m - i;
    if (dp[i][j] != -1) return dp[i][j]; // memoization to use if needed -> save time
    if (word1[i] == word2[j])
        return dp[i][j] = dfs(i + 1, j + 1, word1, word2, m, n);
    else {
            // choose 1 among 3 operations: insert, delete, replace, respectively.
            return dp[i][j] = 1 + min({dfs(i, j + 1, word1, word2,  m,  n), dfs(i + 1, j, word1, word2,  m,  n), dfs(i + 1, j + 1, word1, word2,  m,  n)});
    }
    return dp[i][j];
  }
};
