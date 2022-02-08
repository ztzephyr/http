package main

import (
	"fmt"
)

/**
深度优先搜索
定义：
*/
func s8() {
	fmt.Println("run s8.go")

}

// 102.二叉树的层序遍历(BFS基本框架)
func levelOrder1(root *TreeNode) [][]int {
	if root == nil {
		return nil
	}
	var res [][]int
	var queue []*TreeNode

	queue = append(queue, root)
	// BFS遍历
	for len(queue) > 0 {
		tmpQueue := make([]*TreeNode, 0)
		tmpRes := make([]int, 0)

		for i := 0; i < len(queue); i++ {
			curNode := queue[i]
			tmpRes = append(tmpRes, curNode.Val)
			if curNode.Left != nil {
				tmpQueue = append(tmpQueue, curNode.Left)
			}
			if curNode.Right != nil {
				tmpQueue = append(tmpQueue, curNode.Right)
			}
		}

		// 刷新queue
		queue = tmpQueue

		// 更新res
		res = append(res, tmpRes)
	}
	return res
}

// 111.二叉树的最小深度(BFS求最短路径)
func minDepth(root *TreeNode) int {
	if root == nil {
		return 0
	}

	var queue []*TreeNode
	var step int

	queue = append(queue, root)
	for len(queue) > 0 {
		step++

		tmpQueue := make([]*TreeNode, 0)
		for i:=0;i<len(queue);i++ {
			cur := queue[i]

			// 找到一个节点，无子节点，即为最小深度
			if cur.Left == nil && cur.Right == nil {
				return step
			}

			if cur.Left != nil {
				tmpQueue = append(tmpQueue, cur.Left)
			}
			if cur.Right != nil {
				tmpQueue = append(tmpQueue, cur.Right)
			}
		}
		queue = tmpQueue
	}
	return step
}