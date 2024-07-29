//
// Created by 86380 on 2023/2/2.
//

#ifndef PRO1_TEST_BFS_H
#define PRO1_TEST_BFS_H

#include <iostream>
#include"util.h"
#include<queue>
#include<string>
#include<algorithm>
#include<unordered_set>

using namespace std;

// 计算二叉树的最小深度
class S111 {
public:
    int minDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int depth = 1;  // 有root节点,深度初始为1...
        queue<TreeNode *> q;
        q.push(root);   // BFS的每个元素,即BFS的某一选择...

        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                TreeNode *node = q.front(); // 取出BFS队列中第一个元素...
                q.pop();
                if (node->left == nullptr && node->right == nullptr) {
                    return depth;   // 没有下一层,是叶子节点...
                }
                if (node->left != nullptr) {
                    q.push(node->left); // 为BFS队列添加元素...
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            depth++; // 下一层还有节点,路径加1,,继续处理下一层...
        }
        return depth;
    }
};

// 打开转盘锁
class S752 {
public:
    int openLock(vector<string> &deadends, string target) {

        int res = 0;
        queue<string> q;
        q.push("0000"); // 初始化BFS的某个选择...

        unordered_set<string> deadLocks(deadends.begin(), deadends.end());
        unordered_set<string> visit;
        visit.insert("0000");

        if (target == "0000") {
            return 0;
        }
        if (deadLocks.count("0000")) {
            return -1;
        }

        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                string cur = q.front();  // 站在当前选择下思考...
                q.pop();

                if (deadLocks.count(cur) != 0) {
                    continue; // 无效的选择...
                }
                if (cur == target) {
                    return res;     // 当前选择满足要求...
                }

                for (int i = 0; i < 4; i++) {
                    string up = plusOne(cur, i);
                    if (visit.count(up) == 0) {
                        visit.insert(up);
                        q.push(up);
                    }
                    string down = minusOne(cur, i);
                    if (visit.count(down) == 0) {
                        visit.insert(down);
                        q.push(down);
                    }
                }
            }
            res++;  // 完成当前选择...
        }
        return -1; // 穷举完所有情况,没有return...
    }

    string plusOne(string cur, int i) {
        if (cur[i] == '9') {
            cur[i] = '0';
        } else {
            cur[i] += 1;
        }
        return cur;
    }

    string minusOne(string cur, int i) {
        if (cur[i] == '0') {
            cur[i] = '9';
        } else {
            cur[i] -= 1;
        }
        return cur;
    }
};
















#endif //PRO1_TEST_BFS_H
