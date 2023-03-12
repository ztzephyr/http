//
// Created by 86380 on 2022/10/26.
//

#ifndef PRO1_SORT_TEST_H
#define PRO1_SORT_TEST_H

#include <iostream>
#include <vector>
#include <random>

using namespace std;


/* 归并排序 */
class Merge912 {

    vector<int> temp;   // 临时记录数组中的元素

    void mergeSort(vector<int> &nums) {
        temp = nums;
        int n = nums.size();
        mergeSort(nums, 0, n - 1);
    }

    void mergeSort(vector<int> &nums, int lo, int hi) {
        if (lo == hi) {
            return;
        }
        // 将[lo, hi]区间中的元素分为两边分别处理
        int mid = lo + (hi - lo) / 2;
        mergeSort(nums, lo, mid);
        mergeSort(nums, mid + 1, hi);
        merge(nums, lo, mid, hi);           // 后序遍历到最后位置，逐步开始归并
    }

    void merge(vector<int> &nums, int lo, int mid, int hi) {
        // 使用temp记录nums中[lo,hi]元素, 用于本次合并
        for (int i = lo; i <= hi; i++) {
            temp[i] = nums[i];
        }
        // 使用双指针分别获取元素进行对比, 指针p负责将结果填入nums中对应位置
        int i = lo, j = mid + 1;
        for (int p = lo; p <= hi; p++) {
            if (i == mid + 1) {
                nums[p] = temp[j++];  // 左边已经全部填充完毕，直接填入右边的元素即可
                continue;
            }
            if (j == hi + 1) {
                nums[p] = temp[i++]; // 右边元素已经全部填充，直接填入左边元素即可
                continue;
            }
            if (temp[i] < temp[j]) {
                nums[p] = temp[i++];
            } else {
                nums[p] = temp[j++];
            }
        }
    }
};

/* 快速排序 -- 双路 */
class Quick {

    void quickSort(vector<int> &nums) {
        shuffle(nums);      // 随机打乱nums,防止二叉树的不平衡
        int n = nums.size();
        quickSort(nums, 0, n - 1);
    }

    void shuffle(vector<int> &nums) {
        int n = nums.size();
        default_random_engine e;
        for (int i = 0; i <= n - 1; i++) {
            uniform_int_distribution<int> u(i, n - 1);
            int r = u(e);
            swap(nums[i], nums[r]);
        }
    }

    void quickSort(vector<int> &nums, int lo, int hi) {
        if (lo >= hi) {
            return;
        }
        int p = partition(nums, lo, hi);
        quickSort(nums, lo, p - 1);
        quickSort(nums, p + 1, hi);
    }

    int partition(vector<int> &nums, int lo, int hi) {
        int pivot = nums[lo];

        // 使用双指针逐渐逼近
        int i = lo + 1, j = hi;
        while (i <= j) {
            while (i < hi && nums[i] <= pivot) {
                i++;
            }
            while (j > lo && nums[j] > pivot) {
                j--;
            }
            if (i >= j) {
                break; // 元素全部调换完毕, nums[j]必然是<pivot, 因此退出并将pivot与之调换即可
            }
            // 此时nums[i]>pivot, nums[j]<pivot, 需要执行调换
            swap(nums[i], nums[j]);
        }

        swap(nums[lo], nums[j]);    // nums[j]是最右边一个小于pivot的元素
        return j;
    }
};


#endif //PRO1_SORT_TEST_H
