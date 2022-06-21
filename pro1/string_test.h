//
// Created by 86380 on 2022/11/24.
//

#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>


using namespace std;



/**
 * 贪心思想
 * 分割尽可能多的平衡字符串
 * @param s 一个平衡字符串
 * @return 最多的个数
 */
int balancedStringSplit(string s) {
    int answer = 0;  //记录结果
    int d = 0;       //记录R和L的个数差
    // 贪心：R和L的个数差为0时即找到最小平衡串，是本回合的最优解;继续往右分割
    for (auto c : s) {
        c == 'R' ? d++ : d--;
        if (d == 0) {
            answer++;
        }
    }
    return answer;
}
//////////////////////////////贪心思想/////////////////////////////////////////////


// 最长回文子串
string getLongestPalindrome(string &s, int l, int r) {
    string res;
    // l和r分别往左右扩展且保证回文
    while (l >= 0 && r < s.size() && s[l] == s[r]) {
        l--;
        r++;
    }
    // 截取字符串s[l+1,r-1], 字符个数 r-1-l-1+1
    res = s.substr(l+1, r-l-1);
    return res;
}
/**
 * 思想：遍历字符串s，假设当前为s[i], 使用i构造最长回文子串，也可以使用i和i+1构造，取较长的子串，每次遍历时更新最长子串。
 * 找到字符串s中的最长回文子串
 * @param s
 * @return s中最长的回文子串
 */
string longestPalindrome(string s) {
    string res;     // 记录结果
    // 遍历每个字符，并用其作为回文子串的中心，寻找最长子串
    for (int i =0;i < s.size(); i++) {
        string s1 = getLongestPalindrome(s, i, i);
        string s2 = getLongestPalindrome(s, i, i+1);

        // 更新最长子串
        res = res.size() > s1.size() ? res : s1;
        res = res.size() > s2.size() ? res : s2;
    }
    return res;
}
/////////////////////////////////////////////////////////////////////////////////////


/**
 * 按指定分隔符sep分割字符串s
 * @param s 字符串
 * @param sep 分割符
 * @return 字符串数组
 */
vector<string> splitString(const string& s, char sep) {
    vector<string> res;
    istringstream iss(s);
    string buffer;
    while(getline(iss, buffer, sep)) {
        res.push_back(buffer);
    }
    return res;
}
/////////////////////////////////////////////////////////////////////////////////////

// 贪心
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    int ans = 0;
    int count = 0; // 记录最多能有几个区间
    sort(intervals.begin(), intervals.end(),
         [] (vector<int>& a, vector<int>& b) { return a[1] < b[1];} );

    int end = intervals[0][1];  // 第1个区间的右端点最小
    for (auto& i : intervals) {
        if (i[1] >= end) {
            count++;
            end = i[1];
        }
    }
    ans = (int)(intervals.size() - count);
    return ans;
}

// 判断字符串是否是回文
bool isPalindrome(string s) {
    // 从s中帅选合适的字符，保存在临时的string变量中
    string t;
    for (auto c : s) {
        if (isalnum(c)) {
            t += tolower(c);
        }
    }

    // 判断临时变量t是否是回文
    int left = 0, right = t.size()-1;
    while (left <= right) {
        if (t[left] != t[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// 反转字符串
void reverseString(vector<char>& s) {
    int left = 0, right = s.size()-1;
    while (left <= right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}

// 生成交替字符串最小操作数
int minOperations(string s) {
    int count = 0;
    int left =0, right = 1;
    while(right < s.size()) {
        if (s[right] == s[left]) {
            s[right] = (s[right] == '1' ? '0' :'1');
            count++;
        }
        right++;
        left++;
    }
    return min(count, int(s.size()-count));
}

// 寻找最长子串(不含重复字符)
int lengthOfLongestSubstring(string s) {
    int maxLen = 0;
    unordered_map<char, int> window;

    int l=0, r=0;
    while(r < s.size()) {
        char c = s[r];
        window[c]++;

        // 出现重复元素，从l开始删除，并更新window中的记录
        while(window[c] > 1) {
            char d = s[l];
            window[d]--;
            l++;
        }

        // 更新最长子串
        if (r-l > maxLen) {
            maxLen = r-l+1;
        }
        r++;
    }
    return maxLen;
}

// 罗马数转整数
int romanToInt(string s) {
    int sum = 0;
    unordered_map<char, int> dic = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
    };
    int preNum = dic[s[0]];
    // 遍历时判断是否要减去前面的数
    for (int i=1;i<s.size();i++) {
        int curNum = dic[s[i]];
        if (preNum < curNum) {
            sum -= preNum;
        } else {
            sum += curNum;
        }
        // 更新pre
        preNum = curNum;
    }
    sum += preNum;
    return sum;
}


// 动态规划
vector<int> minOperations1769(string boxes) {

    // d[i]表示，将所有小球移动到第i个盒子所需的最小操作数
    vector<int> dp(boxes.size());

    // 记录boxs中1的总数
    int m = 0;

    // 计算所有小球移动到第0个盒子的最小操作
   for (int i=0;i<boxes.size();i++) {
       if (boxes[i] == '1') {
           dp[0] += i;
           m++;
       }
   }

    // 状态转移方程： dp[i] = dp[i-1]
    // i及i右侧的1， 到达dp[i]， 比到达dp[i-1], 少挪cnt次，用cnt记录i和i的右侧1个数
    // i左侧的1,到达dp[i], 比到达dp[i-1]， 多挪m-cnt次，用m表总1的个数

    // 若第一个数为1,则剩余个数如下
    int cnt = m-(boxes[0]=='1');

   // 开始穷举状态
   for(int i=1; i<boxes.size();i++) {
       dp[i] = dp[i-1] - cnt + (m -cnt);
       // i位置当前为1的话，那么下个状态来说，"i及i右侧"的1会少一个
       if (boxes[i] == '1') {
           cnt--;
       }
   }
    return dp;
}


// 动态规划 买股票的最佳时机
int maxProfit(vector<int>& prices) {
    // dp[i][0]: 第i天手上没有股票，当前的利润
    // dp[i][1]: 第i天手上还有股票，当前的利润
    vector<vector<int>> dp(prices.size(), vector<int>(prices.size()));

    int n = (int)(prices.size());
    dp[0][0] = 0, dp[0][1] = -prices[0];

    // 从i=1天开始
    for (int i=1;i<n;i++) {
        // dp[i][0]: 状态1:第i天, 状态2:不持有股票; 该状态下的利润
        // dp[i-1][0] ===第i-1天不持有股票,第i天不交易==> dp[i][0]
        // dp[i-1][1] ===第i-1天持有股票(当天不可交易),第i天卖出===> dp[i][0]
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]);

        // dp[i][1]: 状态1:第i天, 状态2:持有股票; 该状态下的利润
        // dp[i-1][0] ===第i-1天不持有股票,第i天交易(购买)==> dp[i][1]
        // dp[i-1][1] ===第i-1天持有股票,第i天不交易===> dp[i][1]
        dp[i][1] = max(-prices[i], dp[i-1][1]);
    }
    return dp[n-1][0];
}


// 回溯算法
class s131 { public:
    // 判断全部为小写字母的字符串s是否为回文串
    static bool isPalindrome(string s) {
        int left =0, right=s.size()-1;
        while (left<=right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }

    // 选择列表：假设s被分成n段，每次选择一段，被选完了即触发约束条件
    // 路径： 所有选择做完了，即形成一条路径；此处的路径是若干个回文子串的数组
    // 结果集： 所有的路径组成所有的方案

    vector<vector<string>> res;

    // 回溯算法框架
    void backTrack(string s, int start, vector<string>& path) {
        // base case (做完所有选择后，触发的结束条件)
        // 怎么表示一个选择？从start开始去选择一个段 为一种选择，
        if (start == s.size()) {
            // 产生一个结果
            vector<string> tmp = path;
            res.push_back(tmp);
            return;
        }
        // 做选择---回溯---撤销选择
        for (int i=start;i<s.size();i++) {
            string cur = s.substr(start, i-start+1);
            if (!isPalindrome(cur)) {
                continue;
            }
            // 做出当前选择
            path.push_back(cur);
            // 回溯继续下一个选择
            backTrack(s, i+1, path);
            // 返回上一个选择时，取消当前选择
            path.pop_back();
        }
    }

    // 将字符串s分割成都是回文子串的所有方案
    vector<vector<string>> partition(string s) {
        vector<string> path;
        backTrack(s, 0, path);
        return res;
    }
};

// 1805 计算字符串中不同整数个数
int numDifferentIntegers(string word) {
    // 记录整数字符串
    unordered_set<string> res;

    for (int i =0;i<word.size();i++) {
        // 非数字移动到下一个字符
        if (!isdigit(word[i])) continue;

        // 记录当前数字字符串(包含前导0)
        int j = i;
        string tmp;
        while (isdigit(word[j]) && j < word.size()) {
            tmp += word[j];
            j++;
        }

        // 去除前导0(如果全为0或者只有一个0,tmp为空串，也被插入res中)
        int l = 0;
        while(l<tmp.size()) {
            if (tmp[l] != '0') break;
            l++;
        }
        tmp = tmp.substr(l,tmp.size()-l);
        res.insert(tmp);
        // 更新索引i
        i = j;
    }
    return res.size();
}





class S1781 {
public:

    int getBeauty(string s) {
        // arr[0]代表a ， arr[25]代表z
        vector<int> arr(26);
        for (char v : s) {
            arr[v-'a']++;
        }
        sort(arr.begin(), arr.end());
        int minIndex = 0;
        for (int i =0;i<arr.size();i++) {
            if (arr[i] != 0 ) {
                minIndex = i;
            }
            if (i == arr.size()-1) {
                return 0;
            }
        }
        int res = arr[arr.size()-1] - arr[minIndex];
        return res;
    }

    int beautySum(string s) {
        int res = 0;
        for (int  l = 0;l<s.size();l++) {
            vector<int> cnt(26);
            int maxFreq = 0;
            for (int r =l; r<s.size();r++) {
                cnt[s[r] -'a'] ++;
                maxFreq = max(maxFreq, cnt[s[r]-'a']);
                int minFreq = s.size();
                for (int k = 0; k < 26; k++) {
                    if (cnt[k]>0) minFreq = min(minFreq, cnt[k]);
                }
                res += maxFreq - minFreq;
            }
        }
        return res;
    }
};


























