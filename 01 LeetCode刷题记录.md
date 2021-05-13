##### 227、基本计算器II

给你一个字符串表达式 `s` ，请你实现一个基本计算器来计算并返回它的值。

整数除法仅保留整数部分。

```c
输入：s = "3+2*2"
输出：7
```



题目分析：此题首先默认最前面有个+号，表示你的结果，是要加上后面那串东西的。关键点要把乘除操作都转换成加减，要用一个辅助栈，在遍历字符串时，把每个符号右边的数都压栈，如果发现碰到了乘除算符，那么栈顶的那个元素要被替换掉，换成栈顶元素和下个数计算的结果，代替栈顶元素。这样，最后把栈顶的元素加起来即可。减算符的时候压栈一个负数就行。

知识点：go中使用slice做栈；go中判断字符是否为数字并计算；go中switch中的break机制要清楚；

题后分析：有点乱，下回分析

```go
func calculate(s string) int {

   var stack []int // 辅助栈，用来存结果，最后相加用
   num := 0        //
   op := '+'       // 用来记录数字前面的算符，第一个数默认前面是+
   ans := 0

   for i := 0; i < len(s); i++ {
      // 遍历的时候碰上数字字符串，转换成整数
      if isDigit(s[i]) {
         // 碰上是数字，记录下num(属于上个数)
         num = (num * 10) + int(s[i]-'0') //强制转换成int
      }
      // 碰到不是数字，而是算符，根据上个算符，把上个算符和它右边的数计算后压栈 此处到最后一个数的时候必须压栈，不必等下个算符
      if !isDigit(s[i]) && s[i] != ' ' || i == len(s)-1{
         // 此时的s[i]是下个算符,在此处用上个算符和数，与栈顶元素计算
         switch op {
         case '+':
            // 上个算符为+， 上个数记在num里
            stack = append(stack, num)
         case '-':
            stack = append(stack, -num)
         case '*':
            stack[len(stack)-1] *= num // 直接替换栈顶元素
         case '/':
            stack[len(stack)-1] /= num
         }
         // 上个num已经用过了，重置下, 算符更新下
         num = 0
         op = int32(s[i])
      }
   }
   for _, v := range stack {
      ans += v
   }
   return ans
}
```













##### 242、有效的字母异位词

给定两个字符串 *s* 和 *t* ，编写一个函数来判断 *t* 是否是 *s* 的字母异位词。

**说明:**
你可以假设字符串只包含小写字母。

```c
输入: s = "anagram", t = "nagaram"
输出: true
```



题目分析：字符串专题训练。你可以用数组统计每个字符出现的次数，如果相等，那就是有效的，否则无效。这里有个小技巧优化，就是s出现某字符+1, t中出现某字符时可-1, 这样最后只需要判断数组中数组中是否有非0项，如果没有那就是有效的，否则无效。



知识点分析：go语言中定义数组；go中使用for循环遍历字符串；



题后分析：统一字符出现次数这个数组，可以用切片，但是要用make初始化切片大小，涉及知识点go中使用make初始化切片。拓展一个知识点，go中可以通过==判断两个数组是否相等，但是slice不行。

```go
func isAnagram(s string, t string) bool {
   // 考虑特殊情况，若两字符串长度不一样，肯定false
   if len(s) != len(t) {
      return false
   }
   var count [26]int // 使用数组，也可用slice，但记得用make初始化大小
   for i := 0; i < len(s); i++ {
      count[s[i]-'a']++
      count[t[i]-'a']--
   }
   // 简化成for range写法
   for _, v :=range count {
      if v != 0 {
         return false
      }
   }
   return true
}
```





##### 150、逆波兰表达式求值

根据[ 逆波兰表示法](https://baike.baidu.com/item/逆波兰式/128437)，求表达式的值。

有效的算符包括 `+`、`-`、`*`、`/` 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

-   整数除法只保留整数部分。
-   给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况

```c
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
```





题目分析：根据经验，要使用一个辅助栈来保存操作数，栈中只保留2个操作数；输入是string切片，遍历时碰到算符的时候，计算辅助栈中的2个数，然后继续，直到结束



知识点：go中使用switch；go中使用for range循环；go中字符串转换成数字(strconv.Atoi的使用)；



```go
func evalRPN(tokens []string) int {
   var stack []int
   for i:=0; i<len(tokens);i++ {
      // 碰到算符前，占中操作数的个数
      l:=len(stack)
      switch tokens[i] {
      case "+":
      // 重新构造辅助栈, 切片qie[0:0], 算符只处理其左边两个元素
      stack = append(stack[:l-2], stack[l-2] + stack[l-1])
      case "-":
         stack = append(stack[:l-2], stack[l-2] - stack[l-1])
      case "*":
         stack = append(stack[:l-2], stack[l-2] * stack[l-1])
      case "/":
         stack = append(stack[:l-2], stack[l-2]/stack[l-1])
      default:
         // 非运算符时，将子串转化成数字，方便算符计算
         num, _ := strconv.Atoi(tokens[i])
         stack = append(stack, num)
      }
   }
   return stack[0]
}
```





##### 1221、分割平衡字符串

在一个 平衡字符串 中，'L' 和 'R' 字符的数量是相同的。给你一个平衡字符串 s，请你将它分割成尽可能多的平衡字符串。返回可以通过分割得到的平衡字符串的 最大数量 。

注意：分割得到的每个字符串都必须是平衡字符串。

```c
输入：s = "RLRRLLRLRL"
输出：4
解释：s 可以分割为 "RL"、"RRLL"、"RL"、"RL" ，每个子字符串中都包含相同数量的 'L' 和 'R' 
```



解答：字符串的遍历，遍历过程中，对字符操作；可以用一个指针去切割，切出来的字符串放在栈里；判断条件是栈顶元素为R,当前指针为L，满足则弹出栈去，栈空了说明找到了1个，第1次遍历栈肯定是空的，所以条件中栈不能空；然后继续；

关键点：栈顶元素如果和指针当前遍历的相等，那么就表示不平衡了，此时肯定继续append，等待下次不等，出栈，直到栈为空则找到了一个平衡字符串

知识点：定义go中的栈(切片)； 定义go中的循环；go中往栈添加元素；go中如何比较字符相等；

```go
func balancedStringSplit(s string) int {
   var stack []byte  // 使用切片作为栈，存储字符用byte
   var count int     // 记录返回结果

   length:=len(s)
   for i:=0;i<length;i++ {
      // 栈为空或栈顶元素与s[i]相同，则压栈; 否则出栈
      if len(stack) == 0 || stack[len(stack) - 1] == s[i] {
         stack=append(stack, s[i])
      } else {
         // 出栈，截取子长度，左闭右开
         stack = stack[:len(stack) - 1]
      }
      // 一次遍历中，进行处理后，判断stack是否为空，若空则成功分割1次
      if len(stack) == 0 {
         count++
      }
   }
   return count;
}
```











##### 897、递增顺序搜索树

给你一棵二叉搜索树，请你 **按中序遍历** 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。



