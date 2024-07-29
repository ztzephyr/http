//
// Created by 86380 on 2023/2/6.
//

#ifndef PRO1_TEST_BACKTRACK_H
#define PRO1_TEST_BACKTRACK_H

#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;

// 无重复元素的数组,计算可能的全排列
class S46 {
public:
    vector<vector<int>> res; // 记录所有的全排列...
    vector<int> track; // 记录单个全排列
    vector<vector<int>> permute(vector<int>& nums) {
        backTracking(nums);
        return res;
    }

    void backTracking(vector<int>& nums) {
        if (track.size() == nums.size()) {
            res.push_back(track);   // 选择列表已经为空，无法选择,视为一个全排列...
            return;
        }
        for (int i = 0; i< nums.size();i++) {
            if (find(track.begin(), track.end(), nums[i]) != track.end()) {
                continue; // 元素已被使用,该选择废弃...
            }
            track.push_back(nums[i]);
            backTracking(nums);
            track.pop_back();
        }
    }
};

// 有重复元素的数组,计算所有不重复的全排列
class S47 {
public:
    vector<vector<int>> res; // 记录所有排列...
    vector<int> track;      // 记录单个排列...
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> visit(nums.size()); //记录nums[i]是否被使用...
        backTracking(nums, visit);
        return res;
    }
    void backTracking(vector<int>& nums, vector<int>& visit) {
        if (track.size() == nums.size()) {
            res.push_back(track);  // 选择列表已经用完,没有选择了,记录单个全排列结果...
            return;
        }

        for (int i =0;i<nums.size();i++) {
            if (visit[i]) {
                continue;
            }

            // 使用visit[i】代表的元素，要保证i-1已经被用过,否则可能这个i和i-1会产生重复
            if (i >=1 && nums[i] == nums[i-1] && !visit[i-1] ) {    // i-1未被访问,此时可能和i-2一样,那么重复了...
                continue; // 该选择重复,剪枝废弃...
            }
            visit[i] = 1;
            track.push_back(nums[i]);
            backTracking(nums, visit); // 从后一个元素开始做选择...
            track.pop_back();
            visit[i] = 0;
        }
    }
};

// 对无重复元素的数组, 计算所有的子集
class S78 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        backTrack(nums, 0, path, res);
        return res;
    }

    void backTrack(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& res) {

        res.push_back(path);    // 当前选择,初始为空...
        if (start == nums.size()) {
            return;
        }

        for (int i = start; i< nums.size();i++) { // 有多个选择,每次选择后都是一种结果...
            path.push_back(nums[i]);
            backTrack(nums, i+1, path, res);
            path.pop_back();
        }
    }
};

// 无重复元素的数组, 计算元素个数为k的所有组合
class S77 {
public:
    vector<vector<int>> res;  // 记录最终结果
    vector<int> track;  // 记录单次结果
    vector<vector<int>> combine(int n, int k) {
        backTracking(1, n, k);
        return res;
    }

    void backTracking(int startIdx, int n, int k) {

        if (track.size() == k) {
            res.push_back(track); // 单次选择满足条件...
            return;
        }

        for (int i = startIdx; i<=n;i++ ) {  //当前能做的所有选择...
            track.push_back(i); //加入一个选择...
            backTracking(i+1, n, k);
            track.pop_back();   // 撤销加入的选择,为了在当前的第二次选择...
        }
    }
};

















#endif //PRO1_TEST_BACKTRACK_H
