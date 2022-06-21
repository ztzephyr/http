

#ifndef PRO1_UTIL_H
#define PRO1_UTIL_H


// 设计链表时，定义的链表节点结构
struct ListNode {
    int val;
    ListNode*  next;
    ListNode() : val(), next(nullptr) {};
    explicit ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) : val(x), next(next) {};
};












#endif //PRO1_UTIL_H
