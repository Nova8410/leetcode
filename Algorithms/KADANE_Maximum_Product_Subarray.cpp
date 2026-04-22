#include <algorithm>
#include <vector>

using namespace std;
class Solution {
public:
  int maxProduct(vector<int> &nums) {
    // 3 case: new subarray, neg * neg, maxVal * num
    int res = nums[0];
    int maxVal = 1;
    int negMin = 1;
    for (int num : nums) {
      int preMax = maxVal;
      maxVal = max({num, negMin * num, maxVal * num});
      negMin = min({num, negMin * num, preMax * num});
      res = max(res, maxVal);
    }
    return res;
  }
};
