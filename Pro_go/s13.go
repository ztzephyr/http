package main

import (
	"fmt"
)

/* 模拟题 */
func s13() {
	fmt.Println("run s13.go...")
}

// 67.二进制求和
func addBinary(a string, b string) string {
	var res string
	// 进位标志
	var flag int
	i, j := len(a)-1, len(b)-1
	for i >= 0 || j >= 0 {
		t1, t2 := 0, 0
		// 转换成实际数字
		if i >= 0 {
			t1 = int(a[i]-'0')
		}
		if j>=0 {
			t2=int(b[j]-'0')
		}
		sum := t1 + t2 + flag
		switch sum {
		case 0 :
			flag = 0
			res = "0"+res
		case 1 :
			flag = 0
			res = "1"+res
		case 2 :
			flag = 1
			res = "0"+res
		case 3 :
			flag = 1
			res = "1"+res
		}
		i--
		j--
	}
	// 最后的进位
	if flag == 1 {
		res = "1"+res
	}
	return res
}

// 1945.字符串转化后的各位数字之和
func getLucky(s string, k int) int {
	var ans int
	// 至少转换1次
	for i:=0;i<len(s);i++{
		tmp := int(s[i] - 'a' + 1)
		ans += tmp % 10
		ans += tmp / 10
	}
	// 转换剩余的k-1次
	for k - 1 > 0 {
		cur := ans
		ans = 0
		for cur !=0 {
			ans += cur % 10  // 加个位
			cur /= 10
		}
		k--
	}
	return ans
}

// 258.各位相加
func addDigits(num int) int {
	result := num
	// 累加各位数字
	for result >= 10 {
		// 1次累加各位数字后，刷新result
		cur := result
		result = 0
		for cur != 0 {
			// 取出最后1位数字
			lastNumber := cur%10
			result += lastNumber
			// 更新cur
			cur /= 10
		}
	}
	return result
}

// 289.生命游戏
func gameOfLife(board [][]int)  {
	m, n := len(board), len(board[0])
	res := make([][]int, m)
	for k:=0;k<m;k++{
		res[k] = make([]int, n)
	}
	for i:=0;i<m;i++{
		for j:=0;j<n;j++{
			live := calNum(board, i, j)
			if board[i][j] == 1 {
				if live < 2 {
					res[i][j] = 0
				} else if live == 2 || live == 3{
					res[i][j] = 1
				} else if live >= 3 {
					res[i][j] = 0
				}
			} else {
				if live == 3 {
					res[i][j] = 1
				}
			}
		}
	}
	copy(board, res)
}
func calNum(board [][]int, i, j int) int {
	var count int
	m, n := len(board), len(board[0])

	// 左
	if i>=0 && i < m && j-1 >=0 && j-1 < n {
		if board[i][j-1] == 1 {
			count++
		}
	}
	// 右
	if i>=0 && i < m && j+1 >=0 && j+1 < n {
		if board[i][j+1] == 1 {
			count++
		}
	}
	// 上
	if i-1>=0 && i-1 < m && j >=0 && j < n {
		if board[i-1][j] == 1 {
			count++
		}
	}
	// 下
	if i+1>=0 && i+1 < m && j >=0 && j < n {
		if board[i+1][j] == 1 {
			count++
		}
	}
	// 左上
	if i-1>=0 && i-1 < m && j-1 >=0 && j-1 < n {
		if board[i-1][j-1] == 1 {
			count++
		}
	}
	// 左下
	if i+1>=0 && i+1 < m && j-1 >=0 && j-1 < n {
		if board[i+1][j-1] == 1 {
			count++
		}
	}
	// 右上
	if i-1>=0 && i-1 < m && j+1 >=0 && j+1 < n {
		if board[i-1][j+1] == 1 {
			count++
		}
	}
	// 右下
	if i+1>0 && i+1 < m && j+1 >0 && j+1 < n {
		if board[i+1][j+1] == 1 {
			count++
		}
	}
	return count
}