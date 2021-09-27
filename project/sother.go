package main

import "fmt"

func sOther() {
	fmt.Println("run sOther.go...")

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











