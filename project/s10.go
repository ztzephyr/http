package main

import (
	"fmt"
	"sort"
)

func s10() {
	fmt.Println("run s10.go")

	less1 := func(p1, p2 *Person) bool {
		return  p1.name < p2.name
	}
	less2 := func(p1, p2 *Person) bool {
		return  p1.age< p2.age
	}
	less3 := func(p1, p2 *Person) bool {
		return  p1.lines > p2.lines
	}

	var persons = []Person{
		{"gri", "Go", 100},
		{"ken", "C", 150},
		{"glenda", "Go", 200},
		{"rsc", "Go", 200},
		{"r", "Go", 100},
		{"ken", "Go", 200},
		{"dmr", "C", 100},
		{"r", "C", 150},
		{"gri", "Smalltalk", 80},
	}

	sortBy(less1, less2, less3).Sort(persons)
	fmt.Println(persons)
}

type Person struct {
	name string
	age  string
	lines int
}

type lessFunc func(p1 *Person, p2 *Person) bool

type multiSorter struct {
	persons []Person
	less	[]lessFunc
}

func (ms multiSorter) Len() int { return len(ms.persons) }

func (ms multiSorter) Swap(i, j int) {
	ms.persons[i], ms.persons[j] = ms.persons[j],  ms.persons[i]
}
func (ms multiSorter) Less(i, j int) bool {
	p1, p2 := &ms.persons[i], &ms.persons[j]
	for i:=0; i<len(ms.less)-1;i++{
		less := ms.less[i]
		if less(p1, p2) {
			return true
		} else if less(p2, p1) {
			return false
		}
		// 比较函数比较两个相等，换下个比较函数
		continue
	}
	return ms.less[len(ms.less)-1](p1, p2)
}


// 创建multiSorter实例并初始化比较函数
func sortBy(less ...lessFunc) *multiSorter {
	return &multiSorter{
		less:    less,
	}
}

// 定义multiSorter实例的排序方法
func (ms *multiSorter) Sort(persons []Person) {
	ms.persons = persons
	sort.Sort(ms)
}


