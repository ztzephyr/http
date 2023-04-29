#ifndef HELLO_ALG_LIST_H
#define HELLO_ALG_LIST_H

/* 使用双指针，用链表计算两数之和 */
class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode(-1);
        ListNode *p, *p1, *p2;
        p = dummy; p1 = l1; p2 = l2;
        int carry = 0;

        // 两条链表都走完，且没有进位才结束
        while (p1 != nullptr || p2 != nullptr || carry > 0) {
            int val = carry;        // 先加上上次的进位
            if (p1 != nullptr) {
                val += p1->val;
                p1 = p1->next;
            }
            if (p2 != nullptr) {
                val += p2->val;
                p2 = p2->next;
            }
            carry = val/10;
            val = val % 10;
            p->next = new ListNode(val);
            p = p->next;
        }
        return dummy->next;
    }
};













#endif //HELLO_ALG_LIST_H
