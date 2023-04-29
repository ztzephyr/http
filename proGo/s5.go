package main

import (
	"fmt"
	"math"
)

func s5() {
	fmt.Println("run s5.go ...")
}

// 76.最小覆盖子串(特定条件收缩窗口)
func minWindow(s string, t string) string {
	var res string
	var valid int

	// 记录t中每种类型字符的个数
	need := make(map[byte]int)
	for _, v := range t {
		need[byte(v)]++
	}

	// 初始化窗口数据
	window := make(map[byte]int)
	minLen := math.MaxInt64
	left, right := 0, 0

	for right < len(s) {
		c := s[right]
		right++
		if _, ok := need[c]; ok {
			window[c]++
			if window[c] == need[c] {
				valid++
			}
		}

		for valid == len(need) {
			curLen := right - left
			if curLen < minLen {
				// 更新最小长度
				minLen = curLen
				res = s[left:right]
			}
			d := s[left]
			left++
			if _, ok := need[d]; ok {
				if window[d] == need[d] {
					valid--
				}
				window[d]--
			}
		}
	}
	return res
}

// 219.存在重复元素II(哈希表记录索引)
func containsNearbyDuplicate(nums []int, k int) bool {
	// 满足相等： 用哈希表记录元素索引
	window := make(map[int]int)
	for i:=0;i<len(nums);i++{
		// 当前元素是否记录过
		if _, ok := window[nums[i]]; ok {
			// 当前距离近的元素，索引刷新，即找到的已经是最近的满足条件的了
			if abs(i, window[nums[i]]) <= k {
				return true
			}
		}
		// 记录元素索引
		window[nums[i]] = i
	}
	return false
}

// 220.存在重复元素III(固定长度滑窗)
func containsNearbyAlmostDuplicate(nums []int, k int, t int) bool {
	// 选择窗口起点
	for i:=0;i<len(nums);i++{
		// abs(i-j)<=k 可视为 r最大 = max(i-k, k+i)
		// 固定长度为k+1的窗口
		for r:=i+1; r-i<=k && r<len(nums); r++{
			// r 右移k+1个位置
			if abs(nums[i], nums[r]) <= t {
				return true
			}
		}
	}
	return false
}
func abs(a, b int) int {
	if a > b {
		return a - b
	}
	return b - a
}

// 567.字符串的排列
func checkInclusion(s1 string, s2 string) bool {
	// 记录窗口中的字符
	var valid int
	window := make(map[byte]int)

	// 记录s1中的字符
	need := make(map[byte]int)
	for _, v := range s1 {
		need[byte(v)]++
	}

	left, right := 0, 0
	for right < len(s2) {
		c := s2[right]
		right++

		window[c]++
		if _, ok := need[c]; ok {
			if window[c] == need[c] {
				valid++
			}
		}

		for valid == len(need) {
			// 长度相同更新结果
			if right - left == len(s1) {
				return true
			}

			d := s2[left]
			left++
			if _, ok := need[d]; ok {
				if window[d] == need[d] {
					valid--
				}
			}
			window[d]--
		}
	}
	return false
}

