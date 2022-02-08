package main

import (
	"container/list"
	"fmt"
)

/*  单调队列 */
func s12() {
	fmt.Println("run s12.go...")
	nums := []int{1, -1}

	fmt.Println(maxSlidingWindow(nums, 1))
}




// 单调队列
type MonotonicQueue struct {
	list *list.List
}

func (mq *MonotonicQueue) push(n int) {
	// 将小于n的元素都删除
	for mq.list.Len() != 0 && mq.list.Back().Value.(int) < n {
		value := mq.list.Back()
		mq.list.Remove(value)
		fmt.Println(mq.list.Len())
	}
	mq.list.PushBack(n)
}
func (mq *MonotonicQueue) max() int {
	return mq.list.Front().Value.(int)
}

func (mq *MonotonicQueue) pop(n int) {
	firstElement := mq.list.Front()
	if firstElement.Value.(int) == n {
		mq.list.Remove(firstElement)

	}
}

func maxSlidingWindow(nums []int, k int) []int {
	var res []int
	mq := MonotonicQueue{list:list.New()}
	for i:=0;i<len(nums);i++{

		if i < k-1 {
			mq.push(nums[i])
		} else {

			// 窗口中加入1个元素
			mq.push(nums[i])

			// 记录当前窗口最大值
			res = append(res, mq.max())

			mq.pop(nums[i-k+1])

		}
	}
	return res
}

