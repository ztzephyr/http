#ifndef PRO1_UTIL_H
#define PRO1_UTIL_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


// 公共链表节点数据结构
struct ListNode {
    int val;
    ListNode*  next;
    ListNode() : val(), next(nullptr) {};
    explicit ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) : val(x), next(next) {};
};

// 公共二叉树节点数据结构
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/* 打印数组 */
void printVector(const vector<int>& nums) {
    cout << "[printVector]: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}




























#endif //PRO1_UTIL_H
