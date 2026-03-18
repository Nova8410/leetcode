// Time Complexity: O (m log n)
// Space Complexity: O(1)
#include <vector>
using namespace std;
class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    for (auto &row : matrix) {
      int l{0}, r = row.size() - 1;
      while (l <= r) {
        int mid = l + (r - l) / 2;
        if (row[mid] == target) {
          return true;
        } else if (row[mid] < target) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
    }
    return false;
  }
};
