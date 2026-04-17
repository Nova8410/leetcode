#include <algorithm>
#include <array>
#include <vector>

using namespace std;

class DSU {
public:
  vector<int> Parent, Size;
  DSU(int n) : Parent(n + 1), Size(n + 1) {
    for (int i = 0; i < n + 1; i++)
      Parent[i] = i; // vertex i is its parent initially
  }
  int find(int node) {
    if (Parent[node] != node)
      return find(Parent[node]); // find the parent of parent
    return node;                 // found the root
  }
  bool unionSets(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv)
      return false;
    if (Size[pu] < Size[pv])
      swap(pu, pv);
    Size[pu] += Size[pv];
    Parent[pv] = pu;
    return true;
  }
};
class Solution {
public:
  int minCostConnectPoints(vector<vector<int>> &points) {
    int n = points.size();
    DSU dsu(n);
    vector<array<int, 3>> edges;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int dist =
            abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
        edges.push_back({dist, i, j});
      }
    }
    sort(edges.begin(), edges.end());
    int res = 0;
    for (auto &[dist, u, v] : edges) {
      if (dsu.unionSets(u, v)) {
        res += dist;
      }
    }
    return res;
  }
};
