package main

import (
	"fmt"
	"math"
	"strconv"
)

func s5() {
	fmt.Println("run s5.go ...")
	s := "ADOBECODEBANC";
	t := "ABC"
	fmt.Println(minWindow(s,t))
	x := strconv.Itoa(123)
	fmt.Println(x)






}



// 76.最小覆盖子串
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

