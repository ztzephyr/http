package main

import (
	"fmt"
	"strconv"
	"strings"
)

// 回溯/DFS算法应用
func s7() {
	fmt.Println("run s7.go")
}

// 17.电话号码的字母组合(track不为切片)
func letterCombinations(digits string) []string {
	var res []string
	if len(digits) == 0 {
		return nil
	}
	var backTrack func(digits string, track string, index int)
	backTrack = func(digits string, track string, index int) {
		// base case
		if index == len(digits) {
			res = append(res, track)
			return
		}
		for _, v := range m[digits[index]] {
			x := []byte{byte(v)}
			curStr := string(x)

			track += curStr
			backTrack(digits, track, index+1)
			track = track[:len(track)-1]
		}
	}
	var track string
	backTrack(digits, track, 0)
	return res
}
var m map[byte]string = map[byte]string {
	'2' : "abc",
	'3' : "def",
	'4' : "ghi",
	'5' : "jkl",
	'6' : "mno",
	'7' : "pqrs",
	'8' : "tuv",
	'9' : "wxyz",
}

// 93.复原IP地址(track为切片)
func restoreIpAddresses(s string) []string {
	var res []string
	var backTrack func(track []string, endIdx int, count int)
	backTrack = func(track []string, endIdx int, count int) {
		// base case
		if count == 4 {
			if endIdx == len(s) {
				// 已经选择了4个，且已到s的末端
				tmp := make([]string, 4)
				copy(tmp, track)
				ip := strings.Join(tmp, ".")
				res = append(res, ip)
			}
			return
		}
		// 回溯选择
		for i:=endIdx+1;i<=len(s);i++{
			if s[endIdx] == '0' && i > endIdx + 1 {
				break;
			}
			curIp := s[endIdx:i]
			numIp, _ := strconv.Atoi(curIp)
			if numIp > 255 {
				break
			}
			track = append(track, curIp)
			backTrack(track, i, count+1)
			track = track[:len(track)-1]
		}
	}
	var track []string
	for i:=1;i<=len(s);i++{
		if s[0] == '0' && i > 1 {
			break
		}
		cur := s[:i]
		num, _ := strconv.Atoi(cur)
		if num > 255 {
			break
		}
		track = append(track, cur)
		backTrack(track, i, 1)
		track = track[:len(track)-1]
	}
	return res
}

// 39.组合总和(结果不含重复)
func combinationSum(candidates []int, target int) [][]int {
	var res [][]int
	var backTrack func(track []int, sum int, idx int)
	backTrack = func(track []int, sum int, idx int) {
		// 终止条件
		if idx == len(candidates) {
			return
		}
		if sum == target {
			tmp := make([]int, len(track))
			copy(tmp, track)
			res = append(res, tmp)
			return
		}
		// 直接跳过使用这个数字
		backTrack(track, sum, idx+1)

		// 不跳过这个数字，且剪枝
		if sum < target {
			newSum := sum + candidates[idx]
			track = append(track, candidates[idx])
			backTrack(track, newSum, idx)
			track = track[:len(track)-1]
		}
	}
	var track []int
	backTrack(track, 0, 0)
	return res
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













