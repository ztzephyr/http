//
// Created by 86380 on 2022/12/11.
//

#ifndef PRO1_TEST_LIST_H
#define PRO1_TEST_LIST_H

#include "util.h"


/* 合并2个有序链表 */
class S21 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *dummy = new ListNode(0);  // 虚拟头结点,防止都是空链表的情况
        ListNode* p = dummy;
        ListNode *p1 = list1, *p2 = list2;      // 使用双指针分别获取对应链表元素
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->val < p2->val) {
                p->next = p1;
                p1 = p1->next;
            } else {
                p->next = p2;
                p2 = p2->next;
            }
            p = p->next;
        }
        if (p1 == nullptr) {
            p->next = p2;   // 仅剩余p2链表有数据，直接接上即可
        }
        if (p2 == nullptr) {
            p->next = p1; // 仅剩余p1链表上有数据，直接接上即可
        }
        return dummy->next;
    }
};





class MyLinkedList {

public:
    MyLinkedList() {
        dummyHead = new ListNode();
        size =0;
    };

    // 在头结点前添加1个节点，成为新的头结点
    void addAtHead(int val) {
        ListNode* newHead = new ListNode(val);
        newHead->next = dummyHead->next;
        dummyHead->next = newHead;
        size++;
    }

    // 在尾节点之后添加1个节点
    void addAtTail(int val) {
        ListNode* p = dummyHead;
        while(p->next!=nullptr) {
            p = p->next;
        }
        ListNode* tmp = new ListNode(val);
        p->next = tmp;
        size++;
    }

    // 在索引为index的节点之前添加1个节点;1.index<0,在头结点之前添加;2.index==size,在尾结点之后添加3.index>size不处理
    void addAtIndex(int index, int val) {
        // 索引有效性检查
        if (index < 0) {
            addAtHead(val);
        } else if (index == size) {
            addAtTail(val);
        } else if (index > size) {
            return;
        } else{
            // 移动到索引为index-1的节点
            ListNode* cur = dummyHead;
            for (int i=0;i<index;i++) {
                cur = cur->next;
            }
            ListNode* tmp = new ListNode(val);
            tmp->next = cur->next;
            cur->next = tmp;
            size++;
        }
    }

    // 删除索引为index的节点
    void deleteAtIndex(int index) {
        // 索引有效性检查
        if (index < 0 || index >= size) {
            return;
        }

        // 移动到索引为index-1的节点
        ListNode* cur = dummyHead;
        for (int i=0;i<index;i++) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        size--;
    }

    // 返回索引为index的节点值
    int get(int index) {
        // 索引有效性检查
        if (index < 0 || index >= size) {
            return -1;
        }
        // 移动到索引为index的节点
        ListNode* p = dummyHead;
        for (int i=0;i<index+1;i++) {
            p = p->next;
        }
        return p->val;
    }
private:
    // 虚拟头节点
    ListNode* dummyHead;
    // 链表节点个数
    int size;
};




class S1669 {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {

        // 使用虚拟头结点构造一条结果链表
        ListNode* dummy = new ListNode(0);
        ListNode* p = dummy;

        ListNode* p1 = list1;
        // 遍历list1中[0,a-1]的节点(同时构造)
        for (int i = 0; i< a;i++) {
            p->next = p1;
            p = p->next;
            //更新指向的节点
            p1 = p1->next;
        }

        // 拼接list2
        p->next = list2;

        ListNode* p2 = list2;
        // 遍历到list2最后1个节点
        while(p2->next != nullptr) { p2 = p2->next ; }

        // 使用p1继续遍历list1直到节点b
        for (int j =0;j<b-a+1;j++) {
            p1 = p1->next;
        }

        p2->next = p1;

        return dummy->next;
    }




};
















































#endif //PRO1_TEST_LIST_H
