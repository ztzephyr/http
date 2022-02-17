package main

import (
	"fmt"
)

// 前缀和：原始数组不会被修改，频繁查询某区间的和
func s12() {
	fmt.Println("run s12.go...")
}

// 304.二维区域和检索
type NumMatrix struct {
	preSum [][]int
}
func Constructor304(matrix [][]int) NumMatrix {
	preSum := make([][]int, len(matrix)+1)
	for k, _ := range preSum {
		preSum[k] = make([]int, len(matrix[0])+1)
	}
	for i:=1;i<len(preSum);i++{
		for j:=1;j<len(preSum[0]);j++{
			up, left, upleft := 0, 0, 0
			up = preSum[i-1][j]
			left = preSum[i][j-1]
			upleft = preSum[i-1][j-1]
			preSum[i][j] = up + left - upleft + matrix[i-1][j-1]
		}
	}
	res := NumMatrix{
		preSum : preSum,
	}
	return res
}
func (this *NumMatrix) SumRegion(row1 int, col1 int, row2 int, col2 int) int {
	up, left, upleft := 0, 0, 0
	up = this.preSum[row1][col2+1]
	left = this.preSum[row2+1][col1]
	upleft = this.preSum[row1][col1]
	res := this.preSum[row2+1][col2+1] - up - left + upleft
	return res
}

// 和为k的子数组(哈希表记录前缀和个数)
func subarraySum(nums []int, k int) int {
	var count int
	m := make(map[int]int)
	//构造前缀和
	preSum := make([]int, len(nums)+1)
	for i:=1;i<len(preSum);i++{
		preSum[i] = preSum[i-1] + nums[i-1]
	}
	for i:=0;i<len(preSum);i++{
		need := preSum[i] - k
		if _, ok := m[need]; ok {
			count += m[need]
		}
		//使用哈希表记录个数
		m[preSum[i]]++
	}
	return count
}