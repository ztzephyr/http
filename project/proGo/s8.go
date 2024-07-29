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

// 752.打开转盘锁(BFS求最短路径，避免回头路)
func openLock(deadends []string, target string) int {
	var step int
	visit := make(map[string]bool)
	for _, v := range deadends {
		visit[v] = true
	}
	if _, ok := visit[target]; ok {
		return -1
	}
	var queue []string
	queue = append(queue, "0000")
	step = -1
	for len(queue) > 0 {
		var tmpQueue []string
		step++

		for i := 0; i< len(queue); i++ {
			cur := queue[i]
			if visit[cur] {
				continue
			}
			visit[cur] = true
			if cur == target {
				return step
			}
			// 计算相邻节点
			for k:=0;k<4;k++{
				up := plusOne(cur, k)
				down := minusOne(cur, k)
				tmpQueue = append(tmpQueue, up)
				tmpQueue = append(tmpQueue, down)
			}
		}
		// 刷新queue
		queue = tmpQueue
	}
	return  -1
}
func plusOne(s string, k int) string {
	t := []byte(s)
	if t[k] == '9' {
		t[k] = '0'
	} else {
		t[k] += 1
	}
	return string(t)
}
func minusOne(s string, k int) string {
	t := []byte(s)
	if t[k] == '0' {
		t[k] = '9'
	} else {
		t[k] -= 1
	}
	return string(t)
}
