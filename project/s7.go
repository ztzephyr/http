package main

import (
	"fmt"
)

/**
深度优先搜索
定义：
*/
func s7() {
	fmt.Println("run s7.go")

}

// ld-695 岛屿的最大面积
func maxAreaOfIsland(grid [][]int) int {

	/**
	用了深度优先遍历方法，在遍历每个点的时候
	1. 用dfs其实就是，调用一个会递归的函数
	2. 在dfs中设置终止条件，并且通过标记访问过的点,来避免超时
	3. dfs里面就算面积并返回
	*/

	// 思路：用穷举的方法，遍历每个点
	// 1. 对于每个是1的点，用深搜直到不能搜
	// 2. 每个搜索过的点标记为0，且计算面积

	// 记录已得到的最大面积
	var maxArea int

	// 定义匿名的深搜函数
	var dfs func(grid [][]int, i, j int) int
	dfs = func(grid [][]int, i, j int) int {
		// 边界条件
		if i < 0 || j < 0 || i >= len(grid) || j >= len(grid[0]) {
			return 0
		}

		// 不是1的点直接结束
		if grid[i][j] != 1 {
			return 0
		}

		// 搜索过的标记为0
		grid[i][j] = 0

		// 在当前岛屿面积为1,加上4个方向上的面积
		areaTop := dfs(grid, i, j-1)
		areaBottom := dfs(grid, i, j+1)
		areaLeft := dfs(grid, i-1, j)
		areaRight := dfs(grid, i+1, j)
		return areaTop + areaBottom + areaLeft + areaRight + 1
	}

	// 双重循环遍历每个点
	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[0]); j++ {
			tmpArea := dfs(grid, i, j)
			maxArea = max(maxArea, tmpArea)
		}
	}

	return maxArea
}

// ld-130 被围绕的区域
func solve(board [][]byte) {
	/**
	用深搜，但是只对最外一圈进行深搜
	1.不在边界上或不与边界相连的O要被改为X
	2.深搜边界，找出所有和边界相连的O，先标记为A.那么，未被标记成A的O就是需要改掉的
	3.最后，遍历一次整个矩阵改一下就好
	*/

	row, col := len(board), len(board[0])
	if row == 0 || col == 0 {
		return
	}

	// 用深搜，定义匿名的深搜函数
	var dfs func(i, j int)
	dfs = func(i, j int) {
		// 边界条件(不能够搜索超出矩阵范围,不是O的不搜)
		if i < 0 || j < 0 || i >= row || j >= col || board[i][j] != 'O' {
			return
		}
		// 搜索过的点先标记为A
		board[i][j] = 'A'
		dfs(i, j-1)
		dfs(i, j+1)
		dfs(i-1, j)
		dfs(i+1, j)
	}

	// 主流程：只针对边界进行深搜
	// 深搜第1列和最后1列
	for m := 0; m < row; m++ {
		dfs(m, 0)
		dfs(m, col-1)
	}
	// 深搜第1行和最后1行
	for n := 1; n < col-1; n++ {
		dfs(0, n)
		dfs(row-1, n)
	}

	// 两重循环遍历每个字符
	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[0]); j++ {
			if board[i][j] == 'A' {
				// 和边界相连的O，即不被X包围的O
				board[i][j] = 'O'
			} else if board[i][j] == 'O' {
				// 未被标记到的O,即被X包围的O
				board[i][j] = 'X'
			}
		}
	}
}
