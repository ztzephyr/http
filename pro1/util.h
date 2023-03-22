#ifndef PRO1_UTIL_H
#define PRO1_UTIL_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
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


/* 双向链表的节点类 */
struct Node {
    int key, val;
    Node *pre, *next;
    Node() : key(0), val(0), pre(nullptr), next(nullptr) {}
    Node(int k, int v) : key(k), val(v), pre(nullptr), next(nullptr) {}
};

/* 双端链表类定义 */
class DoubleList {
private:
    Node *dummyHead, *dummyTail;            // 虚拟头节点和虚拟尾结点
    int sz;
public:
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
    unordered_map<int, Node*> m;    // 使用哈希表通过key快速查找一个数据
    DoubleList cache;               // 使用双链表保存每个数据，可进行快速插入和删除
    int cap;                        // LRU缓存最大容量
public:
    explicit LRUCache(int capacity) {
        cap = capacity;
    }
    /* 获取一个数据key对应的val, O(1)的时间复杂度; 该数据被提升为最近使用过的 */
    int get(int key) {
        if (!m.count(key)) {
            return -1;
        }
        makeRecently(key);
        return m[key]->val;
    }

    void put(int key, int value) {
        if (m.count(key) != 0) {
            deleteKey(key);                 // 已经存在该数据，需要在两个数据结构中都删除
            addRecently(key, value);
            return;
        }
        if (cap == cache.size()) {
            removeLeastRecently();          // 删除最近最少使用的那个数据
        }
        addRecently(key, value);
    }
private:

    /* 将某个key对应的数据，提升为最近使用的 */
    void makeRecently(int key) {
        Node* data = m[key];
        cache.remove(data);
        cache.addLast(data);     // 链表尾部的节点作为最近使用的
    }

    /* 删除某个key对应的数据 */
    void deleteKey(int key) {
        Node* data = m[key];
        cache.remove(data);
        m.erase(key);
    }

    /* 以(key,val)键值对，添加一个数据，并提升为最近使用的 */
    void addRecently(int key, int val) {
        Node* data = new Node(key, val);
        cache.addLast(data);
        m[key] = data;
    }

    /* 删除一个最近最少使用的数据 */
    void removeLeastRecently() {
        Node* data= cache.removeFirst();    // 双向链表中第一个元素作为最近最少使用的数据
        int key = data->key;
        m.erase(key);
    }
};






























#endif //PRO1_UTIL_H
