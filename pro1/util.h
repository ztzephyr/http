#ifndef PRO1_UTIL_H
#define PRO1_UTIL_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

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


/* 链表的节点接够 */
struct Node {
    int key, val;
    Node *pre, *next;
    Node() : key(0), val(0), pre(nullptr), next(nullptr) {}
    Node(int k, int v) : key(k), val(v), pre(nullptr), next(nullptr) {}
};

/* 双端链表的实现 */
class DoubleList {

private:
    Node *dummyHead, *dummyTail;  // 虚拟头节点和虚拟尾结点
    int sz;

public:
    // 构造函数
    DoubleList()  {
        dummyHead = new Node(0, 0);
        dummyTail = new Node(0, 0);
        dummyHead->next = dummyTail;
        dummyTail->pre = dummyHead;
        sz = 0;
    }

    // 在尾部添加一个节点
    void addLast(Node* x) {
        x->pre = dummyTail->pre;
        x->next = dummyTail;
        dummyTail->pre->next = x;
        dummyTail->pre = x;
        sz++;
    }

    // 删除链表中的x节点，且时间O(1)
    void remove(Node* x) {
        x->pre->next = x->next;
        x->next->pre = x->pre;
        sz--;
    }

    // 删除链表中的第1个节点，并返回该节点
    Node* removeFirst() {
        if (dummyHead->next == dummyTail) { return nullptr; }
        Node* first = dummyHead->next;
        remove(first);
        return first;
    }

    int size() const { return sz; }
};


class LRUCache {
private:
    unordered_map<int, Node*> m;   // 哈希map
    DoubleList cache;   // 双向链表
public:
    LRUCache(int capacity) {

    }

    int get(int key) {
        if (!m.count(key)) {
            return -1;
        }
        // 将该数据提升为最近使用的
        makeRecently(key);
        return m[key]->val;
    }

    void put(int key, int value) {

    }
private:

    /* 将某个key提升为最近使用的 */
    void makeRecently(int key) {



    }
};



class Difference {
private:
    vector<int> diff;
public:
    /* 输入一个数组nums, 将构造其差分数组 */
    explicit Difference(vector<int>& nums) {
        assert(!nums.empty());
        diff = vector<int>(nums.size(), 0);
        diff[0] = nums[0];
        for (int i = 1; i < diff.size(); i++) {
            diff[i] = nums[i] - nums[i - 1];    /* diff[i]就是nums[i]和nums[i-1]之差 */
        }
    }
    /* 给闭区间[i,j]中每个元素增加val(可以是负数)*/
    void increment(int i, int j, int val) {
        diff[i] += val;
        if (j+1 < diff.size()) {
            diff[j+1] -= val;
        }
    }
    /* 使用差分数组构造结果数组 */
    vector<int> result() {
        vector<int> res(diff.size(), 0);
        res[0] = diff[0];
        for (int i = 0;i < diff.size(); i++) {
            res[i] = res[i-1] + diff[i];
        }
        return res;
    }
};























class S2379 {
public:
    int minimumRecolors(string blocks, int k) {
        unordered_map<char, int> window;   // 记录窗口中w的个数
        int minRes = blocks.size();
        int l=0, r=0;
        while (r < blocks.size()){
            char c = blocks[r++];
            if (c == 'W') {
                window[c]++;
            }
            while (r-l == k) {
                // 更新结果
                minRes = min(minRes, window['W']);
                // 更新窗口
                char d = blocks[l++];
                if (d == 'W') {
                    window[d]--;
                }
            }
        }
        return minRes;
    }
};












#endif //PRO1_UTIL_H
