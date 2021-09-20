package main

import "fmt"

func s6() {
	fmt.Println("s6.go")
}

/**
二叉树
*/

////////////////////////////////////////////////////////////////////////////////////////
/**
知识点1：二叉树的遍历方式
1.前序遍历：
2.中序遍历：按照访问方式，左子树---根节点---右子树
3.后序遍历：
*/

// ld-94 二叉树的中序遍历
func inorderTraversal(root *TreeNode) []int {

	/**
	用到了写1个递归函数遍历二叉树
	1. 中序遍历规则, 左--根--右
	*/

	// 结果即返回一个中序遍历节点值得切片
	var res []int

	// 写1个递归函数，
	var inOrder func(node *TreeNode)
	inOrder = func(node *TreeNode) {
		// 递归结束条件点
		if node == nil {
			return
		}

		// 一直递归到最底层,直到左子树为nil
		inOrder(node.Left)

		// 当前节点左子树为nil， 此时记录下节点值
		res = append(res, node.Val)

		// 左子树处理完，当前节点处理完，递归处理右子树
		// 当前节点如果有右子树，递归调用后，右子树的节点值也会被记录下来
		inOrder(node.Right)
	}

	// 主流程，递归调用根节点
	inOrder(root)

	return res
}
