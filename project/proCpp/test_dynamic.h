//
// Created by 86380 on 2023/2/2.
//

#ifndef PRO1_TEST_DYNAMIC_H
#define PRO1_TEST_DYNAMIC_H

#include<iostream>
#include<vector>
#include <limits>

using namespace std;

// 斐波那契数计算
class S509 {
public:
    int fib(int n) {
        if (n == 0) {
            return n;   // 特殊情况...
        }
        vector<int> dp(n + 1);    // vector初始化...
        dp[0] = 0, dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];  // 自底向向,状态转移...
        }
        return dp[n];
    }
};

// 凑零钱需要的最少硬币个数
class S322 {
public:
    int coinChange(vector<int> &coins, int amount) {
        vector<int> mem(amount + 1, -2);  //备忘录,初始为需要-2个硬币来凑...
        return dp(coins, amount, mem);
    }

    int dp(vector<int> &coins, int amount, vector<int> &mem) {
        if (amount == 0) { return 0; }
        if (amount < 0) {
            return -1;  // 递归终止条件,凑不出来...
        }
        if (mem[amount] != -2) {
            return mem[amount];     // 已经凑过且取了最小值...
        }
        int res = amount + 1;   // 凑amount不可能需要这么多个硬币...
        for (int c : coins) {
            int subProblem = dp(coins, amount - c, mem);
            if (subProblem == -1) {
                continue; // 凑不出来,换下种方式...
            }
            res = min(res, subProblem + 1); // 当前的结果和已进凑过的进行比较...
        }
        if (res == amount + 1) {
            mem[amount] = -1; // 凑不出来...
        } else {
            mem[amount] = res;
        }
        return mem[amount];
    }
};

// 计算最短的编辑距离,即小的操作次数
class S72 {
public:
    int minDistance(string word1, string word2) {
        int i = word1.size() - 1, j = word2.size() - 1;
        vector<vector<int>> mem(i + 1, vector<int>(j + 1, 1000));
        return dp(word1, word2, i, j, mem);
    }

    int dp(string s1, string s2, int i, int j, vector<vector<int>> &mem) {
        if (i == -1) { return j + 1; }    // s1中字符用光,剩下的操作为s2中剩余字符数...
        if (j == -1) { return i + 1; }

        if (mem[i][j] != 1000) { return mem[i][j]; }

        if (s1[i] == s2[j]) {
            mem[i][j] = dp(s1, s2, i - 1, j - 1, mem);
        } else {
            int r1 = dp(s1, s2, i, j - 1, mem) + 1;  // 当前回合执行插入,返回最终总操作数...
            int r2 = dp(s1, s2, i - 1, j, mem) + 1;  // 删除...
            int r3 = dp(s1, s2, i - 1, j - 1, mem) + 1; // 替换...
            mem[i][j] = min(min(r1, r2), r3);
        }

        return mem[i][j];
    }
};

// 计算最大的子数组和
class S53 {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> mem(n, numeric_limits<int>::min());    // 备忘录, 记录每个最小值(以nums[i]为结尾的子序列中的和最小的值)

        int maxSum = numeric_limits<int>::min();
        for (int i = 0;i<n;i++) {
            maxSum = max(maxSum, dp(nums, i, mem));
        }
        return maxSum;
    }

    // 定义dp(nums,i)为以nums[i]为结尾的子数组的和
    int dp(vector<int>& nums, int i, vector<int>& mem) {
        if (i == 0) {
            return nums[0]; // base case, 以nums[0]为结尾的子数组即nums[0]自己...
        }
        if (mem[i] != numeric_limits<int>::min()) {
            return mem[i];
        }
        mem[i] = max(nums[i], nums[i]+dp(nums, i-1, mem));
        return mem[i];
    }

};

// 子序列问题：计算最长递增子序列的长度
class S300 {
public:
    int lengthOfLIS(vector<int> &nums) {
        int n = nums.size();
        vector<int> mem(n, 0);
        int res = 1;
        for (int i = 0; i < n; i++) {
            res = max(res, dp(nums, i, mem)); // 备忘录记录nums[i]为结尾的最长子序列的长度...
        }
        return res;
    }

    // 计算以nums[k]结尾的子序列的最大长度...
    int dp(vector<int> &nums, int i, vector<int> &mem) {
        if (i == 0) {
            mem[i] = 1;  // 以nums[0]结尾的子序列只能是1,且这是base case...
        }
        if (mem[i] != 0) { return mem[i]; }

        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                mem[i] = max(mem[i], dp(nums, j, mem) + 1);
            }
            mem[i] = max(mem[i], 1); // 处理左边没有小于nums[i]的元素...
        }
        return mem[i];
    }
};

// 子序列问题：计算最长公共子序列的长度
class S1143 {
public:
    int longestCommonSubsequence(string text1, string text2) {

        // dp表：dp[i][j]表示s1[0,i-1]和s2[0,j-1]的最长公共子序列长度
        vector<vector<int>> dp(text1.size()+1, vector<int>(text2.size()+1, 0));

        dp[0][0] = 0;
        for ( int i = 1;i<=text1.size();i++) {
            for (int j = 1;j<=text2.size();j++) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }

        return dp[text1.size()][text2.size()];
    }
};

// 子序列问题：计算最长回文子序列的长度
class S516 {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        // dp[i][j]表示s[i,j]中最长回文子序列的长度
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i=0;i<n;i++) {
            dp[i][i] = 1;   // i等于j时,单个字符回文子串长度为1...
        }
        for (int i =n-1;i>=0;i--) {
            for (int j = i+1;j<n;j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i+1][j-1]; // [i+1,j-1]中找回文,加上i和j相等的2...
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]); // 在[i+1,j]或者[i][j-1]中找 回文...
                }
            }
        }
        return dp[0][n-1];
    }
};


class S10 {
public:
    bool isMatch(string s, string p) {

        vector<vector<int>> mem(s.size()+1, vector<int>(p.size()+1, -1));

        return dp(s, 0, p, 0, mem);

    }

    // 计算模式串p[j..]是否可以匹配文本串s[i..]
    bool dp(string s, int i, string p, int j, vector<vector<int>>& mem) {


        int m = s.size(), n = p.size();
        if (j == n) {
            return i == m;
        }

        if (i == m) {
            if ((n-j)%2 == 1) {
                return  false;
            }

            for (; j+1<n;j += 2) {
                if (p[j+1] != '*') {
                    return false;
                }
            }
            return true;
        }

        if (mem[i][j] != -1) {
            return mem[i][j];
        }

        mem[i][j] = false;
        if (s[i] == p[j] || p[j] == '.')  { // 判断当前字符能否匹配上...

            if (j + 1 < p.size() &&  p[j+1] == '*') { // 判断是否存在*通配符...
                bool res1 = dp(s, i, p, j+2, mem); // *匹配0次情况...
                bool res2 = dp(s, i+1, p, j, mem); // *匹配多次情况...
                mem[i][j] = res1 || res2;
            } else {
                mem[i][j] = dp(s, i+1, p, j+1, mem);  // 各自继续往下匹配...
            }

        } else {  // 当前字符匹配不上的情况...

            if (j+1 < p.size() && p[j+1] == '*') {
                // *通配符匹配0次(跳过这个字符吧)
                mem[i][j] =  dp(s, i, p, j+2, mem);
            } else {
                mem[i][j] = 0; // 真的匹配不上...
            }

        }
        return mem[i][j];
    }


};


// 计算解码方法数
class S91 {
public:
    int numDecodings(string s) {
        int n = s.size();
        // dp[i]表示解码前i个数的方法
        vector<int> dp(n+1, 0);
        dp[0] = 1; // dp[0]是定义的特殊的base case...

        for (int i = 1; i<=n;i++) {
            if (s[i-1] != '0') {
                dp[i] = dp[i-1]; // 将第i个数单独解码
            }
            if (i >=2 ) {
                int tmp = (s[i-2]-'0')*10 + s[i-1]-'0';
                if ( tmp >= 10 &&  tmp <= 26 ) {
                    dp[i] += dp[i-2]; // 说明还可以将第i-1个数和第i个数组合进行解码...
                }
            }
        }
        return dp[n];
    }
};

























#endif //PRO1_TEST_DYNAMIC_H
