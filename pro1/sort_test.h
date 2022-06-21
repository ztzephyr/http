//
// Created by 86380 on 2022/10/26.
//

#ifndef PRO1_SORT_TEST_H
#define PRO1_SORT_TEST_H

#include <iostream>
#include <vector>
#include <random>

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////



/**
 * 分区函数，调整数组中[lo, hi]区间的元素，返回数组中某个元素(基数)的下标, 并使得: 1.下标左侧元素<基数; 2.下标右侧元素>基数；
 * @param nums
 * @param lo
 * @param hi
 * @return
 */
int partition(vector<int>& nums, int lo, int hi) {
    // 在数组中选择1个元素作为基数
    int pivot = nums[lo];

    // 对[lo+1, hi]区间的数据处理
    int i = lo + 1, j = hi;
    while (i<=j) {
        // 从左往右审视，索引为lo+1开始，直到找到>pivot的元素nums[i]
        while(i<hi && nums[i] <= pivot) {
            i++;
        }

        // 从右往左审视,索引hi开始,直到找到<pivot的元素nums[j]
        while(j>lo && nums[j] > pivot) {
            j--;
        }

        // 2. 全比基数小或大，则i==j时，跳出去，后面和基数交换即可
        if (i >= j) {
            break;
        }

        //1.比较容易想到的， i<j情况下就是交换，
        swap(nums[i], nums[j]);
    }

    // 和基数交换
    swap(nums[lo], nums[j]);
    return j;
}
/**
 * 对数组nums的[lo, hi]区间排序
 * @param nums
 * @param lo
 * @param hi
 */
void quickSort(vector<int>& nums, int lo, int hi) {
    // 终止条件:当前区域元素个数为0或1时，当前区域已有序
    if (lo >= hi) {
        return;
    }
    // 使用分区函数处理数组，达到效果：1.返回元素索引 2.数组中，索引左侧均小于该元素，右侧均大于该元素 (此处相当于前序遍历位置！)
    int p = partition(nums, lo, hi);

    // 排序左右区域
    quickSort(nums, lo, p-1);
    quickSort(nums, p+1, hi);
}
/**
 * 洗牌算法：将数组nums随机打乱
 * @param nums
 */
void shuffle(vector<int>& nums) {
    int n = (int)nums.size();
    default_random_engine e;    // 先初始化随机引擎
    for (int i = 0; i < n; i++) {
        // 从区间[i,n-1]中随机选择一个索引
        uniform_int_distribution<int> u(i,n-1);
        int r = u(e);
        swap(nums[i], nums[r]);
    }
}
/**
 * 对数组nums快速排序
 * @param nums
 */
void quickSort(vector<int>& nums) {
    // 洗牌算法：随机打乱数组
    shuffle(nums);
    quickSort(nums, 0, nums.size()-1);
}
//////////////////////////////////////////////////////////////////////////////////////





#endif //PRO1_SORT_TEST_H
