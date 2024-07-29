//
// Created by 86380 on 2023/1/31.
//

#ifndef PRO1_TEST_DFS_H
#define PRO1_TEST_DFS_H

#include<iostream>
#include <vector>
#include <string>
#include <set>
#include "util.h"

using namespace std;

// 计算岛屿数量
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

// 剔除不合格岛屿，然后计算岛屿数量
class S1254 {
public:
    int closedIsland(vector<vector<int>> &grid) {
        int res = 0;
        // 上下边界的岛屿非封闭
        for (int j = 0; j < grid[0].size(); j++) {
            dfs(grid, 0, j);
            dfs(grid, grid.size() - 1, j);    // 遍历最下一行...
        }
        // 左右边界岛屿非封闭
        for (int i = 1; i < grid.size() - 1; i++) {
            dfs(grid, i, 0);
            dfs(grid, i, grid[0].size() - 1); // 遍历最右一列...
        }
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 0) {  // 0代表岛屿...
                    res++;
                    dfs(grid, i, j); // 处理相连的所有节点,遍历通常不返回结果...
                }
            }
        }
        return res;
    }

    void dfs(vector<vector<int>> &grid, int i, int j) {
        if (i < 0 || i > grid.size() - 1 || j < 0 || j > grid[0].size() - 1) {
            return;
        }
        if (grid[i][j] == 1) {
            return;     // 无需处理...
        }
        grid[i][j] = 1; // 深搜中的节点处理掉，防止再度访问...

        dfs(grid, i - 1, j);  // 各个方向dfs...
        dfs(grid, i + 1, j);
        dfs(grid, i, j - 1);
        dfs(grid, i, j + 1);
    }
};

// 剔除不合格陆地，计算陆地总面积
class S1020 {
public:
    int numEnclaves(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            dfs(grid, i, 0);    // 对最左和最右列,dfs遍历处理...
            dfs(grid, i, n - 1);
        }
        for (int j = 0; j < n; j++) {
            dfs(grid, 0, j);    // 对最上和最下列，dfs遍历处理...
            dfs(grid, m - 1, j);
        }
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    res++;  // 1表示陆地,计算陆地格子个数...
                }
            }
        }
        return res;
    }

    void dfs(vector<vector<int>> &grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 || i > m - 1 || j > n - 1) {
            return; // 超出搜索边界，停止搜索...
        }
        if (grid[i][j] == 0) {
            return; // 碰到海水格子,该条路径搜索结束...
        }
        grid[i][j] = 0; // 陆地格子变成海水,继续向下搜索...
        dfs(grid, i - 1, j);
        dfs(grid, i + 1, j);
        dfs(grid, i, j - 1);
        dfs(grid, i, j + 1);
    }
};

// 计算每个岛屿的面积,求最大值
class S695 {
public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        int maxArea = 0;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int curArea = dfs(grid, i, j);  // 1是陆地,逐步搜索累加面积...
                    maxArea = max(maxArea, curArea);
                }
            }
        }
        return maxArea;
    }

    int dfs(vector<vector<int>> &grid, int i, int j) {
        int res = 0;
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 || i > m - 1 || j > n - 1) {
            return 0;   // 超出边界，停止搜索...
        }
        if (grid[i][j] == 0) {
            return 0;   // 碰到海水,停止搜索...
        }
        grid[i][j] = 0; // 当前格子由土地变为海水,防止下次又搜索到...

        int up = dfs(grid, i - 1, j);
        int down = dfs(grid, i + 1, j);
        int left = dfs(grid, i, j - 1);
        int right = dfs(grid, i, j + 1);
        res = 1 + up + down + left + right; // 计算每个方向搜索到的陆地个数...
        return res;
    }
};

// 计算子岛屿的个数
class S1905 {
public:
    int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2) {
        int m2 = grid2.size(), n2 = grid2[0].size();
        for (int i = 0; i < m2; i++) {
            for (int j = 0; j < n2; j++) {
                if (grid2[i][j] == 1 && grid1[i][j] == 0) {
                    dfs(grid2, i, j);    // 1代表陆地,若grid2中为陆地grid1中是海水,那么grid2中该岛屿非子岛屿...
                }
            }
        }
        int res = 0;
        for (int i = 0; i < m2; i++) {
            for (int j = 0; j < n2; j++) {
                if (grid2[i][j] == 1) {
                    res++;    // 1是陆地，进行计数并dfs处理掉相连的格子...
                    dfs(grid2, i, j);
                }
            }
        }
        return res;
    }

    // dfs仅遍历且处理该岛屿的格子！
    void dfs(vector<vector<int>> &grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 || i > m - 1 || j > n - 1) {
            return;     // 超出搜索边界，停止搜索...
        }
        if (grid[i][j] == 0) {
            return;     // 0是水域,不进行dfs搜索...
        }
        grid[i][j] = 0; // 陆地变水域...
        dfs(grid, i - 1, j);
        dfs(grid, i + 1, j);
        dfs(grid, i, j - 1);
        dfs(grid, i, j + 1);
    }
};

// 记录dfs路径,计算不同岛屿的数量
class S694 {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        set<string> res;
        int m = grid.size(), n = grid[0].size();
        for (int i=0;i<m;i++) {
            for (int j=0;j<n;j++) {
                if (grid[i][j] == 1) {
                    string tmp;
                    string& r = tmp;
                    dfs(grid, i, j, r, "000");    // 仅代表从哪个方向来，初始无...
                    res.insert(tmp);
                }
            }
        }
        return res.size();
    }

    void dfs(vector<vector<int>> &grid, int i, int j, string &s, string dir) {
        int m = grid.size(), n = grid[0].size();
        if (i<0||j<0||i>m-1||j>n-1) {
            return;
        }

        if (grid[i][j] == 0) {
            return;     // 0是海水,停止搜索...
        }

        grid[i][j] = 0;  // 陆地格子处理层海水...
        s+=dir;
        s+=".";     // 记录从哪个方向来这个格子...

        dfs(grid, i-1, j, s, "1");  // 向左搜索...
        dfs(grid, i+1, j, s, "2");
        dfs(grid, i, j-1, s, "3");
        dfs(grid, i, j+1, s, "4");

        int len = s.length();
        s+= ("-" + dir);
        s +=".";      // 递归返回，撤销当前节点加的路径...
    }

};




// dfs计算二叉树节点个数
class S1145 {
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        TreeNode* node = dfsFindNode(root, x);
        int leftSize = dfs(node->left);
        if (leftSize >= (n+1)/2) { return  true;}   // 左子树区域...
        int rightSize = dfs(node->right);
        if (rightSize >= (n+1)/2) {return true;}    // 右子树区域...
        int remain = n - 1 - leftSize - rightSize ; // 父节点区域...
        return remain >= (n+1)/2;
    }

    int dfs(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left = dfs(root->left);
        int right = dfs(root->right);
        return 1 + left + right;
    }

    TreeNode* dfsFindNode(TreeNode* root, int x) {
        if (root == nullptr) { return nullptr;}
        if (root->val == x) {
            return root;
        }
        TreeNode* left = dfsFindNode(root->left, x);
        if (left!= nullptr) {return left;}
        TreeNode* right = dfsFindNode(root->right, x);
        if (right!= nullptr) {return right;}
        return nullptr;
    }
};



















#endif //PRO1_TEST_DFS_H
