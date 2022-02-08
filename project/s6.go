package main

import (
	"fmt"
	"math"
)

/**
二叉树
1.性质：如果对二叉树进行中序遍历，得到的值是递增有序的
*/
func s6() {
	/**
	1. 二叉树的前中后序遍历；
	 */
	fmt.Println("s6.go")
}


////////////////////////////////////////////////////////////////////////////////////////
/**
知识点1： 二叉树的递归
1. 虽然递归和二叉树并无太紧密的关系，但是二叉树具有天然递归条件
2. 递归首先考虑终止条件！
*/

// ld-226 翻转二叉树
func invertTree(root *TreeNode) *TreeNode {

	// Tips： 拿到这到题的时候，应该明白，一个最简单的二叉树如何翻转,
	// Tips： 二叉树首先考虑递归
	if root == nil {
		return nil
	}

	// 任何二叉树，先分别翻转它的左右子树
	l := invertTree(root.Left)
	r := invertTree(root.Right)

	root.Left, root.Right = r, l
	return root
}



////////////////////////////////////////////////////////////////////////////////////////
/**
知识点2：二叉树的前、中、后序遍历
1.前序遍历：
2.中序遍历：按照访问方式，左子树---根节点---右子树
3.后序遍历：
*/

// ld-94 二叉树的中序遍历
func inorderTraversal(root *TreeNode) []int {

	/**
		用到中序遍历， 左---根---右
		1.递归的方式中序遍历，本质在第一次对左进行递归调用时，会一直递归，直到返回
		2.等到返回时，开始执行最后一次的调用点之后的函数
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

// ld-98 验证二叉搜索树
func isValidBST(root *TreeNode) bool {

	/**
		考察二叉树的中序遍历: 左-根-右
		0.通过定义匿名的递归函数实现中序遍历
		1.中序遍历时，检查每个节点值，是否满足条件
		2.条件就是： 上一个节点 < 当前节点值 < 下一个节点
	 */

	// pre初始化设为最小值
	pre := math.MinInt64

	// 定义一个递归函数，用来中序遍历
	var dfs func(node *TreeNode) bool
	dfs = func(node *TreeNode) bool {
		// 既然有递归，必须有终止条件
		if node == nil {
			return true
		}

		// 1.中序遍历的左, 从第1个遍历到根节点
		if !dfs(root.Left) {
			return false
		}

		// 2.中序遍历的中, 判断当前节点值是否大于上一个节点值
		if node.Val <= pre {
			return false
		}
		// 更新pre
		pre = node.Val

		// 3.中序遍历的右, 判断右是否ok
		return dfs(node.Right)
	}

	// 用定义好的dfs来进行中序遍历, 遍历过程中，不满足则返回false
	return dfs(root)
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
知识点3：二叉树的层序遍历
1. 典型的BFS
 */

// ld-102 二叉树的层序遍历
func levelOrder(root *TreeNode) [][]int {

	if root == nil {
		return [][]int{}
	}

	// 记录层序遍历的结果
	var res [][]int

	// BFS的维护队列，首先加入根节点
	queue := []*TreeNode{root}


	// 队列中有节点，就处理(最后一层的后面就没有节点了)
	for len(queue) > 0 {

		// 1. 记录下一层的节点
		var tmpQueue []*TreeNode

		// 2. 记录当前层的节点值
		tmpRes := []int{}

		// 遍历一下当前层的每个节点
		for i:=0;i<len(queue);i++ {
			node := queue[i]
			tmpRes = append(tmpRes, node.Val)

			// 若当前节点具有左右子节点,记录下来
			if node.Left != nil {
				tmpQueue = append(tmpQueue, node.Left)
			}
			if node.Right != nil {
				tmpQueue = append(tmpQueue, node.Right)
			}
		}

		// 当前层获取的都拿到了，更新下
		queue = tmpQueue
		res = append(res, tmpRes)
	}
	return res
}


















