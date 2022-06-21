//
// Created by 86380 on 2023/1/31.
//

#ifndef PRO1_TEST_DFS_H
#define PRO1_TEST_DFS_H

#include <vector>

using namespace std;

class S200 {
public:
    int numIslands(vector<vector<char>> &grid) {
        int res = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    res++;      // 记录当前岛屿...
                    dfs(grid, i, j);   // 处理该岛屿的所有节点...
                }
            }
        }
        return res;
    }

    void dfs(vector<vector<char>> &grid, int i, int j) {
        if (i < 0 || j < 0 || i > grid.size() - 1 || j > grid[0].size() - 1) {
            return;   // dfs遍历边界条件...
        }
        if (grid[i][j] == '0') {
            return;  // 不需处理的节点...
        }
        grid[i][j] = '0';   // 标记该节点

        dfs(grid, i - 1, j);  // dfs遍历的方向...
        dfs(grid, i + 1, j);
        dfs(grid, i, j - 1);
        dfs(grid, i, j + 1);
    }
};


#endif //PRO1_TEST_DFS_H
