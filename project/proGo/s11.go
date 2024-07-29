package main

import (
	"container/heap"
	"fmt"
)

/* 使用heap构造优先队列 */
/**
1.最大堆：
 */
func s11() {
	fmt.Println("run s11.go...")

}

// 703.数据流中的第K大元素
type KthLargest struct {
	minHeap IntHeap
	k int
}
func Constructor(k int, nums []int) KthLargest {
	kl := KthLargest{
		k : k,
	}
	for _, v := range nums {
		kl.Add(v)
	}
	return kl;
}
func (this *KthLargest) Add(val int) int {
	heap.Push(&this.minHeap, val)
	if this.minHeap.Len() > this.k {
		heap.Pop(&this.minHeap)
	}
	return this.minHeap[0]
}
type IntHeap []int
func (h IntHeap) Len() int { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i]}
func (h *IntHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}
func (h *IntHeap) Pop() interface{} {
	old := *h
	x := old[len(old)-1]
	*h = old[:len(old)-1]
	return x
}


// 912.排序数组
func sortArray(nums []int) []int {
	var res []int
	var minHeap IntHeap
	for _, v := range nums {
		heap.Push(&minHeap, v)
	}
	for minHeap.Len() > 0 {
		tmp := heap.Pop(&minHeap).(int)
		res = append(res, tmp)
	}
	return res
}

























































type Twitter struct {
	userMap map[int]*user	// 推特系统使用map保存所有用户
	timeStamp int			// 推特系统时间
}

// 用户类：保存用户信息
type user struct{
	userId int
	followed map[int]*user
	head *tweet				// 推文头节点
}

// 推文类：保存推文信息
type tweet struct {
	tweetId int
	time int
	next *tweet
}

// 实现heap接口，构建优先队列
//type PriorityQueue []*tweet
//
//func (pq PriorityQueue) Len() int { return len(pq) }
//
//func (pq PriorityQueue) Less(i, j int) bool {
//	return pq[i].time > pq[j].time
//}
//
//func (pq PriorityQueue) Swap(i, j int) {
//	pq[i], pq[j] = pq[j], pq[i]
//}
//
//func (pq *PriorityQueue) Push(x interface{}) {
//	item := x.(*tweet)
//	*pq = append(*pq, item)
//}
//
//func (pq *PriorityQueue) Pop() interface{} {
//	old := *pq
//	n := len(old)
//	item := old[n-1]
//	old[n-1] = nil  // avoid memory leak
//	*pq = old[0 : n-1]
//	return item
//}
//
//
//func Constructor() Twitter {
//	return Twitter{
//		userMap: make(map[int]*user),
//	}
//}
//
//// 1. 推特系统必须有，根据userId获取用户的方法
//func (this *Twitter) getUser(userId int) *user {
//	if _, ok := this.userMap[userId]; !ok {
//		// 当前userId不存在
//		u := &user {
//			userId:userId,
//			followed: make(map[int]*user),
//		}
//		this.userMap[userId] = u
//	}
//	return this.userMap[userId]
//}
//
//// 2. 推特必须有，获取当前时间的方法
//func (this *Twitter) getTime() int {
//	this.timeStamp++
//	return this.timeStamp
//}
//
//func (this *Twitter) PostTweet(userId int, tweetId int)  {
//	// 获取用户
//	u := this.getUser(userId)
//	// 构造1条推特
//	twt := tweet{
//		tweetId: tweetId,
//		time:    this.getTime(),
//		next:    u.head,
//	}
//	u.head = &twt
//}
//
//
//func (this *Twitter) GetNewsFeed(userId int) []int {
//	var res []int
//	// 初始化优先队列
//	pq := make(PriorityQueue, 0)
//
//	// 遍历当前用户的关注列表，包括自己
//	u := this.getUser(userId)
//	if u.head != nil {
//		//将自己的第1条推文加入
//		pq = append(pq, u.head)
//	}
//
//	for _, v := range u.followed {
//		// 将自己关注列表的第1条推文加入
//		curTweet := v.head
//		if curTweet == nil {
//			continue
//		}
//		pq = append(pq, curTweet)
//	}
//	heap.Init(&pq)
//
//	// 返回最多10条记录
//	for len(pq) != 0 {
//		if len(res) == 10 {
//			break
//		}
//		item := heap.Pop(&pq).(*tweet)
//		res = append(res, item.tweetId)
//		if item.next != nil {
//			heap.Push(&pq, item.next)
//		}
//
//
//	}
//	return res
//}
//
//
//func (this *Twitter) Follow(followerId int, followeeId int)  {
//	// 获取关注者，和被关注者
//	u1 := this.getUser(followerId)
//	u2 := this.getUser(followeeId)
//	if _, ok := u1.followed[followeeId]; !ok {
//		u1.followed[followeeId] = u2
//	}
//}
//
//
//func (this *Twitter) Unfollow(followerId int, followeeId int)  {
//	u1 := this.getUser(followerId)
//	if _, ok := u1.followed[followeeId]; ok {
//		delete(u1.followed, followeeId)
//	}
//}