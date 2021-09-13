package main

import (
	"fmt"
)

/**
	排序
 */
func s1() {
	fmt.Println("run s1.go ...")
}

/////////////////////////////////////////////////////////////////////////////////

/**
	知识点1：基本类型的切片排序函数
	int类型切片排序, sort.Ints(a []int)
	float64类型切片排序, sort.Float64s(a []float64)
	string类型切片排序, sort.Strings(a []string)
*/







/////////////////////////////////////////////////////////////////////////////////

/**
	知识点2：Go的切片排序函数:
	sort.Slice(slice interface{}, less func(i, j int) bool)
	1.可以用来对任意切片排序，后面的less函数用来定义排序规则.
	2. Slice可以用SliceStable代替，官方推荐更加稳定.
 */

// ld-56 合并区间
func merge(intervals [][]int) [][]int {
	/**
		用到切片排序函数sort.Slice，对左边界进行了一个排序；
		1.然后利用已排好序的切片，先把第0个放到结果中；
		2.每次比较结果切片的右端点，若>左端点则开始合并；重复直到合并完成
	 */
	return nil
}

// ld-179 最大数
func largestNumber(nums []int) string {
	/**
		用到切片排序函数sort.Slice，对字符串切片进行排序:
		1.自定义的排序规则是：Ascall值，第1个字符串拼接第2个字符串 > 第2个字符串拼接第1个字符串；
		2.然后可以把排好序的字符串拼接起来可以得到最大数字，记得处理全为0的特殊情况；
	 */
	return ""
}

// ld -49 字母异位词
func groupAnagrams(strs []string) [][]string {
	/**
		用到切片排序函数sort.Slice, 对字符串转换的[]byte切片进行排序;
		1.自定义的排序规则是：普通的按Ascall值从小到大排序；
		2.利用每个异位词经过排序后都相同，申请了一个键为string,值为[]string的map，
	  	  将每个字符串保存到，排序后的键对应的值中，这样提取出了一组一组的异位词;
	 */
	return nil
}



