package main

import (
	"fmt"
	"sort"
)


/**
二分搜索(要求有序数组)
 */
func s2() {
	fmt.Println("run s2.go ...")
}

// 34.在排序数组中查找元素的第1个位置和最后1个位置
func searchRange(nums []int, target int) []int {
	left := leftBound(nums, target)
	right := rightBound(nums, target)
	return []int{left, right}
}
func leftBound(nums []int, target int) int {
	left, right := 0, len(nums)
	for left < right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			right = mid
		} else if nums[mid] < target {
			left = mid + 1
		} else if nums[mid] > target {
			right = mid
		}
	}
	// 全部<target + 全部>target
	if left == len(nums) || nums[left] != target {
		return -1
	}
	return left
}
func rightBound(nums []int, target int) int {
	left, right := 0, len(nums)
	for left < right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			left = mid + 1
		} else if nums[mid] < target {
			left = mid + 1
		} else if nums[mid] > target {
			right = mid
		}
	}
	// 全部>target + 全部<target
	if left == 0 || nums[left-1] != target {
		return -1
	}
	return left - 1
}


// 35.搜索插入位置(二分搜索左侧边界，target不存在时返回的是应该插入的位置)
func searchInsert(nums []int, target int) int {
	//搜索左侧边界,当target不存在数组nums中时，返回值可以做以下几种解读：
	//1、返回的这个值是nums中大于等于target的最小元素索引。
	//2、返回的这个值是target应该插入在nums中的索引位置。
	//3、返回的这个值是nums中小于target的元素个数
	left, right := 0, len(nums)
	for left < right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			right = mid
		} else if nums[mid] < target {
			left = mid + 1
		} else if nums[mid] > target {
			right = mid
		}
	}
	// 全部<target + 全部>target
	if left == len(nums) || nums[left] != target {
		return left
	}
	return left
}


// 875.珂珂吃香蕉(二分搜索-画图应用)
func minEatingSpeed(piles []int, h int) int {
	// 速度最小为0,最大为一堆香蕉的最大根数
	left, right := 1, getMaxCount(piles) + 1
	for left < right {
		mid := left + (right-left)/2
		if f(piles, mid) == h {
			right = mid
		} else if f(piles, mid) < h {
			right = mid
		} else if f(piles, mid) > h {
			left = mid + 1
		}
	}
	return left
}
// 计算吃完所有香蕉需要的时间
func f(piles []int, k int) int {
	var hour int
	fmt.Println(piles)
	for _, v := range piles {
		fmt.Println(v)
		hour += int(v)/k
		if v%k != 0 {
			hour++
		}
	}
	return hour
}
// 计算一堆香蕉的最大根数
func getMaxCount(piles []int) int {
	var maxCount int
	for _, v := range piles {
		if v > maxCount {
			maxCount = v
		}
	}
	return maxCount
}


// 1011.在D天内送达包裹的能力
func shipWithinDays(weights []int, days int) int {
	minCap, maxCap := 0, 0
	for _, v := range weights {
		maxCap += v
		if minCap < v {
			minCap = v
		}
	}
	left, right := minCap, maxCap+1
	for left < right {
		mid := left + (right-left)/2
		if fw(weights, mid) == days {
			right = mid
		} else if fw(weights, mid) < days {
			right = mid
		} else if fw(weights, mid) > days {
			left = mid + 1
		}
	}
	return left
}
// 计算运载能力为k时,送掉传输带上所有包裹的时间
func fw(weights []int, k int) int {
	var days int
	sum := 0
	for i:=0;i<len(weights);i++{
		sum += weights[i]
		if sum > k {
			days++
			sum = weights[i]
		}
	}
	days++
	return days
}












// ld-374 猜数字大小
func guessNumber(n int) int {
	/**
	用了二分查找的方法去找数字，根据接口决定二分查找是否继续
	*/

	l, r := 1, n
	for l <= r {
		mid := l + (r-l)/2
		conditon := guess(mid)
		if conditon == -1 {
			r = mid - 1
		} else if conditon == 1 {
			l = mid + 1
		} else {
			return mid
		}

	}
	return -1
}

// ld-69 x的平方根
func mySqrt(x int) int {
	/**
	用到二分查找去找一个数，该数的平方小于x，且从[0，x)找是有序的
	1. 用二分法找一个满足条件的数，每满足条件时，记录一次
	2. 0到x相当于索引，其平方可认为是数组的某索引对应的值
	*/

	// 记录结果值
	var ans int

	l, r := 0, x
	for l <= r {
		mid := l + (r-l)/2
		if mid*mid <= x {
			ans = mid
			// 可能不是最大的满足条件的, 继续生成闭区间[mid+1, r]寻找
			// 注意，此时如果新生成的区间中不会再有满足条件的，那么也不会更新ans
			l = mid + 1
		} else {
			// 发现该mid已经大于了x, 生成闭区间[l, mid-1]寻找
			r = mid - 1
		}
	}
	return ans
}

///////////////////////////////////////////////////////////////////////////////
/**
	知识点1：Go的二分查找函数(sort.search)
	sort.Search(n int, f func(int) bool) int
	1.要求有序，在n个元素中,使用"二分查找"算法查找指定target
	2.满足f(index)=true的条件下，从[0,n)中取出一个最小的index;
	3.会假定f(index)=true, 那么f(index+1)=true;（因此查找某个值时，应该用f>=target)
	4.[0,n)中没有满足条件的index时，此时返回n, 需特别注意

	sort.SearchInts(a []int, x int) int
	sort.SearchFloat64s(a []float64, x float64) int
	sort.SearchStrings(a []string, x string) int
	1.直接实现了3种基本类型的二分查找，即在[0,n-1]找到一个最小的>=x的元素对应索引；
	2.需要自行处理找不到或者找到大于目标值的情况
*/


// ld-33 搜索旋转排序数组
func search2(nums []int, target int) int {

	/**
	通过处理成有序数组后，利用二分查找的方法找
	1.用int类型的二分查找函数，在[0,n-1]的索引上找
	*/

	// 计算出旋转后的数组断点位置
	breakPoint := len(nums)
	for i := 0; i < len(nums)-1; i++ {
		if nums[i] > nums[i+1] {
			breakPoint = i + 1
		}
	}

	// 提取出有序数组, 且都是升序
	s1 := nums[:breakPoint]
	s2 := nums[breakPoint:]

	if nums[0] <= target {
		idx := sort.SearchInts(s1, target)
		if idx < len(s1) && s1[idx] == target {
			return idx
		} else {
			return -1
		}
	} else {
		idx := sort.SearchInts(s2, target)
		if idx < len(s2) && s2[idx] == target {
			return idx + breakPoint
		} else {
			return -1
		}
	}
}
