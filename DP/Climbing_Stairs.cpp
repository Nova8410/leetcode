#include <vector>
using namespace std;

class Solution {
public:
  int climbStairs(int n) {
    if (n < 3)
      return n;
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i < n + 1; i++) {
      dp[i] = dp[i - 2] + dp[i - 1];
    }
    return dp[n];
  }
};
