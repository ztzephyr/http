//
// Created by 86380 on 2023/2/27.
//

#ifndef PRO1_TEST_STACK_H
#define PRO1_TEST_STACK_H

#include <stack>

// 用2个栈实现队列
class MyQueue {
private:
    std::stack<int> s1;
    std::stack<int> s2;
public:
    MyQueue() {}

    void push(int x) {
        s1.push(x);
    }

    int pop() {
        int front = peek(); // 调用peek保证s2非空
        s2.pop();
        return front;
    }

    int peek() {
        // 从s1中弹出元素依次压入s2中,若s2中非空则每次弹出元素即可作为队首元素
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }

    bool empty() {
        return s1.empty() &&  s2.empty();
    }
};










#endif //PRO1_TEST_STACK_H
