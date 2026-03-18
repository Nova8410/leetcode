// Time complexity: O(n)
// Space complexity: O(1)
// solution only applies to lowercase English letters (a-z)
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
  bool isAnagram(string s, string t) {
    if (s.size() != t.size())
      return false; // base case
    vector<int> count(26, 0);
    for (int i{0}; i < s.size(); i++) {
      count[s[i] - 'a']++;
      count[t[i] - 'a']--;
    }
    for (int val : count) {
      if (val != 0)
        return false;
    }
    return true;
  }
};
