package main

import (
	"fmt"
	"math"
	"sort"
)

func sOther() {
	fmt.Println("run sOther.go...")
	//message := "ABBCDCDAB"
	//keys := "BAC"

	nums1:=[]int{1,2,2,1}
	nums2:=[]int{2,2}
	fmt.Println(intersect(nums1, nums2))



}

/**
	二叉搜索树(BST)
	1.BST的每个节点node,左子树节点的值都比node的值小，右子树节点的值都比node的值大.
	2.BST的每个节点node,它的左子树和右子树都是BST.
 */

// ld-230 二叉搜索树中第k小的元素(中序遍历)
func kthSmallest(root *TreeNode, k int) int {

	// 定义1个slice存储中序遍历的节点值
	var nums []int

	// 定义递归函数中序遍历(左--根--右)
	var inOrder func(node *TreeNode)
	inOrder = func(node *TreeNode) {
		if node == nil {
			return
		}

		inOrder(node.Left)

		/* 中序遍历位置 */
		nums = append(nums, node.Val)

		inOrder(node.Right)
	}

	// 主流程：开启一个中序遍历递归函数
	inOrder(root)

	return nums[k-1]
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/**
哈希表的使用
 */








////////////////////////////////////////////////////////////////////////
/** 单链表(一)
1.递归反转整个链表
2.递归反转链表的前N个节点
3.递归反转链表的一部分
4.递归K个一组反转链表
 */

// ld-206 反转链表(反转整个链表)
func reverseList(head *ListNode) *ListNode {
	// 明确递归函数的定义： 输入一个节点head，将「以head为起点」的链表反转，并返回反转之后的头结点

	// 我认为还需要处理head是nil的情况
	if head == nil {
		return nil
	}

	// 链表中只有一个节点的时候, head.Next为nil，反转就是返回自己
	if head.Next == nil {
		return head
	}
	last := reverseList(head.Next)
	head.Next.Next = head
	head.Next = nil
	return last
}

// 反转链表的前N个节点，并且返回新的头节点
var successor *ListNode
func reverseN(head *ListNode, n int) *ListNode {
	// 记录下第n+1个节点
	if n == 1 {
		successor = head.Next
		return head
	}

	last := reverseN(head.Next, n-1)
	head.Next.Next = head
	head.Next = successor
	return last
}

// ld-92 反转链表II(反转链表的一部分)
func reverseBetween(head *ListNode, left int, right int) *ListNode {
	// 反转位置left到位置right的元素，并返回头节点

	// 递归终止条件
	if left == 1 {
		// 想当于反转前right个元素，并返回头节点
		return reverseN(head, right)
	}

	// 对于head.Next, 相当于反转位置left-1到right-1的元素, 然后返回head.next
	head.Next = reverseBetween(head.Next, left-1, right-1)
	return head
}

// ld-25 K个一组反转链表
func reverseKGroup(head *ListNode, k int) *ListNode {
	// 递归定义: k个一组反转链表，并返回新的头节点
	a, b := head, head

	// 区间[a,b）定义要反转的k个元素
	for i:=0;i<k;i++{
		// 如果不足k个,则会出现为b为nil的情况, 当前以a开始，不足k，那么不必反转，直接返回head
		if b == nil {
			return head
		}
		b = b.Next
	}

	newHead := reverseN(a, k)
	a.Next = reverseKGroup(b,k)
	return newHead
}


///////////////////////////////////////////////////////////////////////
/** 单链表(二)
1.判断回文单链表
 */

// ld-234 回文链表
func isPalindrome(head *ListNode) bool {
	left := head

	// 定义匿名递归遍历函数.
	var traverse func(right *ListNode) bool
	traverse = func(right *ListNode) bool {
		if right == nil {
			// nil 满足回文
			return true
		}
		res := traverse(right.Next)
		res = res && right.Val == left.Val

		// 更新左指针
		left = left.Next
		return res
	}

	// 主流程
	return  traverse(head)
}



// message = "ABBCDCDABC"
// keys "BAC"
func findCount(message string, keys string)  string {
	window := make(map[byte]int)
	need :=  make(map[byte]int)
	valid := 0
	//resCount :=0
	maxLength := math.MaxInt64
	start:=0
	for _, v := range keys {
		need[byte(v)]++
	}

	left , right := 0, 0
	for right < len(message) {
		c:= message[right]
		right++

		if _, ok := need[c]; ok {
			window[c]++
			if window[c] == need[c] {
				valid++
			}
		}

		for valid == len(need) {

			if right-left < maxLength {
				 start = left
				 maxLength = right -left
			}

			d:= message[left]
			left++

			if _, ok := need[d]; ok {
				if window[d] == need[d] {
					valid--
				}
				window[d]--
			}

		}

	}


	return  message[start:start+maxLength]
}



func intersect(nums1 []int, nums2 []int) []int {
	var res []int
	for i:=0;i<len(nums1);i++ {
		target := nums1[i]

		sort.Ints(nums2)
		left, right := 0, len(nums2)
		for left < right {
			mid := left + (right-left)/2
			if nums2[mid] == target {
				res = append(res, target)
				nums2[mid] = -1
				break;
			} else if nums2[mid] < target {
				left = mid + 1
			} else if nums2[mid] > target {
				right = mid
			}
		}
	}

	return res
}















