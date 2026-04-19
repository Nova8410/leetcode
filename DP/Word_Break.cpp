#include <vector>
#include <string>
using namespace std;
class Solution {
public:
  bool wordBreak(string s, vector<string> &wordDict) {
    vector<bool> dp(s.size() + 1, false);
    dp[s.size()] = true;
    for (int i = s.size() - 1; i >= 0; i--) {
      for (const string &word : wordDict) {
        // check boundary and each word if match s[i:]
        if ((i + word.size() <= s.size()) && (s.substr(i, word.size()) == word))
          dp[i] = dp[i + word.size()];
        if (dp[i])
          break; // no need to iterate the other words in wordDict
      }
    }
    return dp[0];
  }
};
