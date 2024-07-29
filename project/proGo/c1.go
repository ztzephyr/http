package main

import (
	"fmt"
)

func c1() {
	fmt.Println("run c1.go")
	wordDict := []string{"cats","dog","sand","and","cat"}
	s := "catsandog"
	fmt.Println(wordBreak(s, wordDict))
}



func wordBreak(s string, wordDict []string) bool {
	curQueue := make([]string, 0)		// 构造当前队列
	var step int						// 记录步数
	visit := make(map[string]bool)		// 避免回头路

	// 初始化当前队列和步数
	curQueue = append(curQueue, wordDict...)
	step = 0
	for _, v := range curQueue {
		visit[v] = true
	}

	// BFS遍历
	for len(curQueue) != 0 {

		// 更新步数
		step++

		// 构造下个队列
		nextQueue := make([]string, 0)
		for i:=0;i<len(curQueue);i++{
			for j:=0;j<len(wordDict);j++{
				newWord := curQueue[i] + wordDict[j]
				if newWord == s {
					return true
				}
				if newWord != s && !visit[newWord] {
					nextQueue = append(nextQueue, newWord)
					visit[newWord] = true
				}
			}
		}
		curQueue = nextQueue
	}

	return false
}