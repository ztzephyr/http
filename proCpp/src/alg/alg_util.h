#ifndef PRO1_ALG_UTIL_H
#define PRO1_ALG_UTIL_H

#include<vector>
#include<unordered_map>

using namespace std;


class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;                        // 记录每一层的元素
        if (numRows < 1) {
            return res;
        }
        vector<int> firstRow(1, 1);            // 先装入第1层
        res.push_back(firstRow);
        for (int i = 2; i <= numRows; i++) {
            vector<int> preRow = res.back();
            vector<int> nextRow = generateNextRow(preRow);
            res.push_back(nextRow);
        }
        return res;
    }

    vector<int> generateNextRow(vector<int> &preRow) {
        vector<int> nextRow(1, 1);            // 下一层的第一个元素固定为1
        for (int i = 0; i < preRow.size() - 1; i++) {
            int val = preRow[i] + preRow[i + 1];
            nextRow.push_back(val);
        }
        nextRow.push_back(1);                           // 下一层最后一个元素固定为1
        return nextRow;
    }
};


#endif