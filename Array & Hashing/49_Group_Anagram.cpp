#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    if (strs.size() == 0)
      return {};
    unordered_map<string, vector<string>> res;
    for (string &s : strs) {
      string s_key = s;
      sort(s_key.begin(), s_key.end());
      res[s_key].push_back(s);
    }
    vector<vector<string>> result;
    for (auto &pair : res) {
      result.push_back(pair.second);
    }
    return result;
  }
};
