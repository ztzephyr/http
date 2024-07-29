package main

import (
	"fmt"
)

// 差分数组：频繁对原始数组，某个区间进行增减
func s15() {
	fmt.Println("run s15.go...")

}

// 370.区间加法(差分数组前缀和，即原数组对应索引值)
func getModifiedArray(length int, updates [][]int) []int {
	n := length
	res := make([]int, n)
	diff := make([]int, n)
	for i:=1;i<n;i++{
		diff[i]= res[i] - res[i-1]
	}
	for k:=0;k<len(updates);k++{
		i := updates[k][0]
		j := updates[k][1]
		val := updates[k][2]
		diff[i] += val
		if j+1 < n {
			diff[j+1] -= val
		}
	}
	// 根据差分数组构造结果数组
	res[0] = diff[0]
	for i:=1;i<n;i++{
		res[i] = res[i-1] + diff[i]
	}
	return res
}

