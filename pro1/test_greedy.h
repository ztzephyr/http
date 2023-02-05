//
// Created by 86380 on 2023/2/4.
//

#ifndef PRO1_TEST_GREEDY_H
#define PRO1_TEST_GREEDY_H

#include <vector>
#include <algorithm>

using namespace std;


class S1789 {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        int res = 0; // 一开始只能构造出0...
        sort(coins.begin(), coins.end());
        for (int c : coins) {
            if (c > res +1) {
                break;  // 前面的元素最多能完成构造[0,res], 若c大于res+1,则res+1无法构建...
            }
            res = res + c ;  // 此时c小于等于res+1,已构建了[0,res],能继续构建到[c+0,c+res], 最大可加res...
        }
        return res+1;
    }
};










#endif //PRO1_TEST_GREEDY_H
