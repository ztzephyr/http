package main

import (
	"fmt"
)

/* 位运算 */
func s14() {
	fmt.Println("run s13.go...")

}

// 191.位1的个数(消除二进制表示最后一个1)
func hammingWeight(num uint32) int {
	var count int
	for num != 0 {
		num = num & (num-1)
		count++
	}
	return count
}

// 2的幂(n&n-1:只有一个1)
func isPowerOfTwo(n int) bool {
	var count int
	for n != 0 {
		n = n&(n-1)
		count++
	}
	if count == 1 {
		return true
	}
	return false
}

// 540.有序数组中的单一元素(1个数和0异或为自己，和自己异或为0)
func singleNonDuplicate(nums []int) int {
	var res int
	for _, v := range nums {
		res ^= v
	}
	return res
}