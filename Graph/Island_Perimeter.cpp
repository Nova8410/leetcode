#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int>> grid;
    vector<vector<bool>> visited;
    int r;
    int c;
    int dfs(int i, int j) 
        {   
            if (i < 0 || j < 0 || i >= r || j >= c || grid[i][j] == 0)
                return 1;
            if (visited[i][j])
                return 0;
            visited[i][j] = true;
            return dfs(i + 1, j) + dfs(i - 1, j) + dfs(i, j - 1) + dfs(i, j + 1);
        }
public:
    
    int islandPerimeter(vector<vector<int>>& grid) {
        this->grid = grid; // reuse 3 following:
        r = grid.size();
        c = grid[0].size();
        visited = vector<vector<bool>>(r, vector<bool>(c, false));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] == 1)
                    return dfs(i, j);
            }
        }
        return 0;
    }
};