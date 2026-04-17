#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
// Prim's (The first solution is not optimal, recommend using the second one)
class Solution {
public:
  int minCostConnectPoints(vector<vector<int>> &points) {
    int n = points.size();
    unordered_map<int, vector<pair<int, int>>> adj;
    for (int i = 0; i < n; i++) {
      int x1 = points[i][0];
      int y1 = points[i][1];
      for (int j = i + 1; j < n; j++) {
        int x2 = points[j][0];
        int y2 = points[j][1];
        int dist = abs(x1 - x2) + abs(y1 - y2);
        adj[i].push_back({dist, j});
        adj[j].push_back({dist, i});
      }
    }
    int res = 0;
    unordered_set<int> visited;
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        minH; // {cost, point}
    minH.push({0, 0});
    while (visited.size() < n) {
      int cost = minH.top().first;
      int i = minH.top().second;
      minH.pop();
      if (visited.find(i) != visited.end())
        continue;
      res += cost;
      visited.insert(i);
      for (const auto &nei : adj[i]) {
        if (visited.find(nei.second) == visited.end()) {
          // cost and i
          minH.push({nei.first, nei.second});
        }
      }
    }
    return res;
  }
};
// O(N^2 logN)
/*
OPTIMAL APPROUCH
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size(), node = 0;
        vector<int> dist(n, 100000000);
        vector<bool> visit(n, false);
        int edges = 0, res = 0;

        while (edges < n - 1) {
            visit[node] = true;
            int nextNode = -1;
            for (int i = 0; i < n; i++) {
                if (visit[i]) continue;
                int curDist = abs(points[i][0] - points[node][0]) +
                               abs(points[i][1] - points[node][1]);
                dist[i] = min(dist[i], curDist); update k[v]
                if (nextNode == -1 || dist[i] < dist[nextNode]) {
                    nextNode = i; UPDATE vertex
                }
            }
            res += dist[nextNode];
            node = nextNode;
            edges++;
        }
        return res;
    }
    O (N^2)
};
*/