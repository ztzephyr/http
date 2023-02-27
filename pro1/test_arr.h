//
// Created by 86380 on 2022/11/27.
//

#ifndef PRO1_ARR_TEST_H
#define PRO1_ARR_TEST_H

#include <iostream>
#include <vector>
#include<cmath>
#include <algorithm>
#include<numeric>
#include <random>

using namespace std;

// 动态规划：0-1背包
int knapsack(int W, int N, vector<int>& wt, vector<int>& val) {
    // 定义dp数组， dp[i][w]表示在第i个物品下,背包剩余容量为w下，做出选择后,可装的最大价值
    vector<vector<int>> dp (N+1, vector<int>(N+1, 0));

    // 如此定义则是按第1个物品开始计算的逻辑，i=0被表示成了没有物品的特殊情况;
    for (int i=0; i <= N; i++) {
        // 背包可装重量的每种情况
        for (int w=1;w<=W;w++) {
            // 背包容量不足，只能不装入
            if (w-wt[i-1] <= 0) {
                dp[i][w] = dp[i-1][w];
            } else {
                // 装入或者不装入背包，取价值大的
                dp[i][w] = max(
                        // 不把第i个物品装入背包
                        dp[i-2][w],
                        // 把第i个物品装入背包
                        val[i-2] + dp[i-1][w-wt[i-1]]
                );
            }
        }
    }
    return dp[N][W];
}
////////////////////////////////////////////////////////////////////////////////

// 动态规划: 凑零钱
int dp(vector<int>& coins, int amount, vector<int>& mem) {
    // 明确状态： 1.可选的硬币列表  2. 剩余要凑的金额数
    // 明确选择： 选择coins中的一个元素
    // 定义状态转移函数： dp(coins, amount)表示使用coins数组中的硬币凑出amount金额需要的硬币最少个数
    // 写成状态转移逻辑: dp(coins[], amount) = dp(coins[i], amount-coins[i]) + 1

    // 过滤不可能凑出的值
    if (amount < 0) return -1;
    // 过滤凑金额为0的情况
    if (amount == 0) return 0;

    // 记录凑金额为amount需要的硬币最小个数,初始化为amount+1
    int res = amount + 1;

    // 查找备忘录
    if (mem[amount] != -66) {
        return mem[amount];
    }

    // 暴力穷举每种情况
    for (auto& coin : coins) {
        // 计算子问题: 凑金额为amount-coin需要的硬币最少数
        int subRes = dp(coins, amount-coin, mem);
        // 子问题凑不出来，则跳过该情况
        if (subRes == -1) continue;

        // 子问题可以凑出来，更新凑amount需要的硬币最少个数
        res = min(res, subRes + 1);
    }
    // 判断是否所有子问题均凑不出来?
    if (res == amount + 1) {
        mem[amount] = res;
        return -1;
    }

    // 记录当前结果到备忘录中
    mem[amount] = res;

    return res;
}
int coinChange(vector<int>& coins, int amount) {
    // 备忘录：记录凑每种金额需要的最小硬币数, 初始化为无效值-2
    vector<int> mem(amount+1, -66);
    return dp(coins, amount, mem);
}
/////////////////////////////////////////////////////////////////////////////////

// 贪心：加油站
class S134 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // 贪心：若站点i到达站点j油量会变为负数，那么[i,j]中任一站点到达j站点油量都会变为负数!
        // 因为车在站点i时,油量最少都是0,那么到[i+1,j)中的任一站点油量的增量>=0; 从[i+1,j-1]中任何站点出发，缺少增量更加不能到达站点j

        // 判断是否不够环绕一圈消耗
        int sum = 0;
        for (int k=0;k<gas.size();k++) {
            sum += gas[k]-cost[k];
        }
        if (sum < 0) { return -1;}

        // 假设起点为start
        int start = 0;
        // 记录当前油量,
        int tank = 0;
        int n = (int)gas.size();
        for (int i=0;i<n;i++) {
            // 计算到达i+1站点的剩余油量
            tank += gas[i]-cost[i];
            if (tank < 0) {
                // 因为贪心, [start,i+1]失败,更新起点为i+1
                start = i+1;
                // 起点重置，邮箱重置
                tank = 0;
            }
        }
        // 由于题目说存在解必唯一，最后即使i==n-1, start更新为n,那也是这个解
        return start == n ? 0: start;
    }
};
/////////////////////////////////////////////////////////////////////////////////

// 贪心: 最少操作次数
class S1775 {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        // 贪心思想: 每次尽可能变化更多的量,来更快的使两个数组差值最小

        // 数组元素取值范围[1,6], 和较大的数组全变为1，和较小的数组全变为6; 较小的仍较小则无解
        if ( nums1.size() * 6 < nums2.size() * 1  || nums2.size() * 6 < nums1.size() * 1 ) {
            return -1;
        }

        // 计算nums1和nums2的和, 且保证是形成sum1>sum2的情况
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);

        // 计算差值
        int d = sum1- sum2;
        if (d < 0) {
            d = -d;
            swap(nums1, nums2);
        }

        // 记录能使出的最大变化量, 对应的个数; 变化量有6个分别为 0,1,2,3,4,5
        int cnt[6] = {};

        // 对于num1, 要减小元素值, 能少的最大量为 nums1[i] - 1
        for (int v : nums1) { cnt[v-1]++; }
        // 对于nums2, 要增加其元素值, 能增大的最大量为 6-nums2[i]
        for (int v : nums2) { cnt[6-v]++; }

        // 贪心的先选择使用最大变化量
        int res = 0;
        for (int i = 5; i>0;i-- ) {
            // 如果当前选择的, 最大变化量i * 个数cnt[i] >= d, 那么直接用就可以，最后一次变化可以不用变化i就OK
            if (i * cnt[i] >= d) {
                return res + (d + i - 1)/i;     // 向上取整，若余1，那么1+i-1/i;若余i-1,那么2i-2/i=2-2/i;i>=2都是ok的，1本来就ok
            }
            // 更新差值: 用掉所有最大变化量
            d -= i *cnt[i];
            res += cnt[i];
        }
        return res;
    }
};
////////////////////////////////////////////////////////////////////////////////


class S1144 {
public:
    int movesToMakeZigzag(vector<int>& nums) {

        int res1 = 0, res2 = 0;

        // 第一种情况，奇数索引小于左右两边
        for (int i =0 ; i< nums.size(); i++) {
            int left = i ?  nums[i-1] : INT32_MAX;
            int right = (i == nums.size()-1) ? INT32_MAX : nums[i+1];
            if ( i % 2 != 0) {
                int tmp = nums[i] - (min(left, right)-1);
                res1 += max(tmp, 0);
            }
        }

        for (int i = 0;i < nums.size();i++) {
            int left = i ?  nums[i-1] : INT32_MAX;
            int right = (i == nums.size()-1) ? INT32_MAX : nums[i+1];
            if (i %2 == 0) {
                res2 += max(nums[i]-(min(left, right)-1), 0);
            }
        }

        return min(res1, res2);
    }
};




// 回溯：最接近目标价格的甜点成本
void dfs(vector<int>& toppingCosts, int k, int curCost, int target, int& res) {

    // base case
    if (k == toppingCosts.size()) {
        // 没有可选择的配料, 计算当前成本是否需要更新
        if (res == -1 || abs(curCost-target) < abs(res-target) ||
            (abs(curCost-target) == abs(res-target) &&  curCost < res) ) {
            res = curCost;
            return;
        }
    }
    dfs(toppingCosts, k+1, curCost, target, res);
    dfs(toppingCosts, k+1, curCost+toppingCosts[k], target, res);
    dfs(toppingCosts, k+1, curCost+toppingCosts[k]*2, target, res);
}
int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {

    // 记录结果
    int res = -1;
    for (auto& b : baseCosts) {
        dfs(toppingCosts, 0, b, target, res);
    }
    return res;
}


// 数组 +1
vector<int> plusOne(vector<int>& digits) {
    int n = (int)digits.size();
    for (int i=n-1;i<n;i--) {
        if (digits[i] != 9) {
            digits[i]++;
            // 发现某为不为9,直接就返回
            return digits;
        }
        digits[i] = 0;
    }

    // 全是9的情况
    vector<int> res(n+1);
    res[0] = 1;
    return res;
}





class S384 {
public:
    S384(vector<int>& nums) {
        this->nums = nums;
    }
    vector<int> reset() {
        return nums;
    }
    vector<int> shuffle() {
        vector<int> res = nums;
        int n = res.size();
        default_random_engine e;
        for (int i = 0;i < n ;i++) {
            // 从[i, n-1]中任选一个数交换
            uniform_int_distribution<int> u(i, n-1);
            int r = u(e);
            swap(res[i], res[r]);
        }
        return res;
    }
private:
    vector<int> nums;
};













#endif //PRO1_ARR_TEST_H
