package main

import (
	"fmt"
	"math"
)

/**
递归
*/

func s9() {
	fmt.Println("run s9.go")
}

// ld-98 验证二叉搜索树
func isValidBST1(root *TreeNode) bool {

	/**
	用了递归的方式遍历二叉树，并判断每个节点值的范围
	1. 终止条件是用递归处理nil节点的时候
	2. 递归中碰到不符合条件的返回fasle， 直到终止条件也没有返回false那么就返回true
	*/

	// 定义1个递归函数
	var dfs func(node *TreeNode, lower, upper int) bool
	dfs = func(node *TreeNode, lower, upper int) bool {
		// 当遍历到了没有节点的情况,没有问题，那就结束了
		if node == nil {
			return true
		}

		// 1.左子树节点值 <= 当前节点值 <= 右子树节点值
		if node.Val <= lower || node.Val >= upper {
			return false
		}

		// 对于左子树里面的值, 递归判断有如下条件:
		// 1.上界upper最大为当前节点值, 即node.Val
		// 2.下界lower最小为最大的负数，即传入的最小值lower
		resLeft := dfs(node.Left, lower, node.Val)

		// 对于右子树里面的值， 递归有如下条件：
		// 1.上界upper, 是个大于右子树节点值的数，无最大，即传入的最大值upper
		// 2.下界lower, 最小得大于当前节点值,即node.Val
		resRight := dfs(node.Right, node.Val, upper)

		return resLeft && resRight
	}

	// 根节点的值没有限制， 在最小和最大之间就可以
	return dfs(root, math.MinInt64, math.MaxInt64)
}
