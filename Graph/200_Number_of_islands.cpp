class Solution {
    int d[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
private:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        if (r < 0 || c < 0 || r >= grid.size() 
            || c >= grid[0].size() || grid[r][c] == '0') return;
        grid[r][c] = '0';
        for (int i = 0; i < 4; i++) {
            dfs(grid, r + d[i][0], c + d[i][1]);
        }
    }
public:

    int numIslands(vector<vector<char>>& grid) {
        int island = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '0') continue;
                dfs(grid, i, j);
                island++;
            }
        }
        return island;
    }
};
