package main

import (
	"fmt"
	"sort"
)

/**
	二分查找
	1. 用这个方法，要求有序数组,升序降序处理略有不同
*/

func s2() {
	fmt.Println("run s2.go ...")
}

///////////////////////////////////////////////////////////////////////////////
/**
	知识点1：最基础经典的二分查找算法
	1. 要求就是在一个有序的条件
	2. 你可以根据对查找出来的值的要求，来决定是否继续查询，还是保留当前结果
*/

// ld-704 二分查找
func search(nums []int, target int) int {
	/**
	1.最经典的二分查找,也是最基础的二分查找
	2.二分查找在一个闭区间中进行寻找，每次取查找范围的中点mid
	3.闭区间的中点如何计算，闭区间则满足l<=r
	*/

	l, r := 0, len(nums)-1
	for l <= r {
		mid := l + (r-l)/2
		if nums[mid] == target {
			return mid
		} else if nums[mid] > target {
			r = mid - 1
		} else {
			l = mid + 1
		}
	}
	return -1
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

// ld-704 二分查找
func search1(nums []int, target int) int {
	/**
	1.用了Go的排序接口，然后用的Go的二分查找接口
	2.Go的二分查找接口返回n是找不到，返回idx对应值不等于目标值是找到后面去了
	*/

	// 定义要返回的索引
	var idx int

	// 排序后查找
	sort.Ints(nums)
	idx = sort.Search(len(nums), func(i int) bool {
		return nums[i] >= target
	})

	// 若找到的元素更大，或者找不到满足条件的，手动返回-1
	if idx <= len(nums) && nums[idx] == target {
		return idx
	}
	return -1
}

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
