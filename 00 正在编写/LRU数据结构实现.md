
​	LRU 缓存淘汰算法是一种常用策略。LRU 的全称是 Least Recently Used，也就是说我们认为最近使用过的数据应该是是「有用的」，很久都没用过的数据应该是无用的，内存满了就优先删那些很久没用过的数据。



要求实现的数据结构：

```c++
class LRUCache {
public:
    /* 接收capacity参数作为缓冲最大容量 */
    LRUCache(int capacity);
    
    /* 获取一个数据key对应的val， O(1)的时间复杂度 */
    int get(int key);
    
    /* 以(key,val）键值对形式插入一个数据, O(1)时间复杂度 */
    void put(int key, int value);
};
```



### 一、使用自定义的双链表实现(造轮子)

LRU数据结构需要使用哈希表+双链表实现。假设链表尾部节点是最近使用过的节点。



自定义的双链表类和节点类，提供的接口：

```c++
/* 双链表的节点类 */
struct Node {
    int key, val;
    Node *pre, *next;
};

/* 自定义的双链表类 */
class DoubleList {
private:    
    Node *dummyHead, *dummyTail;
    int sz;
public:
    void addLast(Node* x);			/* 在尾部加入一个节点 */
    void remove(Node* x);			/* 删除链表中的x节点 */	
    Node* removeFirst();			/* 删除首节点,并返回该节点 */
    int size() const;				/* 返回链表中节点的个数 */
};
```



```c++
class LRUCache {
private:
    unordered_map<int, Node*> m;    // 使用哈希表通过key快速查找一个数据
    DoubleList cache;               // 使用双链表保存每个数据，可进行快速插入和删除
    int cap;                        // LRU缓存最大容量
public:
    explicit LRUCache(int capacity) {
        cap = capacity;
    }
    /* 获取一个数据key对应的val, O(1)的时间复杂度; 该数据被提升为最近使用过的 */
    int get(int key) {
        if (!m.count(key)) {
            return -1;
        }
        makeRecently(key);
        return m[key]->val;
    }

    void put(int key, int value) {
        if (m.count(key) != 0) {
            deleteKey(key);                 // 已经存在该数据，需要在两个数据结构中都删除
            addRecently(key, value);
            return;
        }
        if (cap == cache.size()) {
            removeLeastRecently();          // 删除最近最少使用的那个数据
        }
        addRecently(key, value);
    }
private:

    /* 将某个key对应的数据，提升为最近使用的 */
    void makeRecently(int key) {
        Node* data = m[key];
        cache.remove(data);
        cache.addLast(data);     // 链表尾部的节点作为最近使用的
    }

    /* 删除某个key对应的数据 */
    void deleteKey(int key) {
        Node* data = m[key];
        cache.remove(data);
        m.erase(key);
    }

    /* 以(key,val)键值对，添加一个数据，并提升为最近使用的 */
    void addRecently(int key, int val) {
        Node* data = new Node(key, val);
        cache.addLast(data);
        m[key] = data;
    }
    
    /* 删除一个最近最少使用的数据 */
    void removeLeastRecently() {
        Node* data= cache.removeFirst();    // 双向链表中第一个元素作为最近最少使用的数据
        int key = data->key;
        m.erase(key);
    }
};
```



双链表的实现：

```c++
/* 双向链表的节点类 */
struct Node {
    int key, val;
    Node *pre, *next;
    Node() : key(0), val(0), pre(nullptr), next(nullptr) {}
    Node(int k, int v) : key(k), val(v), pre(nullptr), next(nullptr) {}
};

/* 双端链表类定义 */
class DoubleList {
private:
    Node *dummyHead, *dummyTail;            // 虚拟头节点和虚拟尾结点
    int sz;
public:
    DoubleList()  {
        dummyHead = new Node(0, 0);
        dummyTail = new Node(0, 0);
        dummyHead->next = dummyTail;
        dummyTail->pre = dummyHead;
        sz = 0;
    }

    // 在尾部添加一个节点
    void addLast(Node* x) {
        x->pre = dummyTail->pre;
        x->next = dummyTail;
        dummyTail->pre->next = x;
        dummyTail->pre = x;
        sz++;
    }

    // 删除链表中的x节点，且时间O(1)
    void remove(Node* x) {
        x->pre->next = x->next;
        x->next->pre = x->pre;
        sz--;
    }

    // 删除链表中的第1个节点，并返回该节点
    Node* removeFirst() {
        if (dummyHead->next == dummyTail) { return nullptr; }
        Node* first = dummyHead->next;
        remove(first);
        return first;
    }

    int size() const { return sz; }
};
```





### 二、使用list+哈希表实现



C++中list(双向链表)支持的常用操作：

```c++
std::list<int> lst;
void push_back(int x);		/* 在链表尾部添加一个元素 */
void push_front(int x);		/* 在链表的头部添加一个元素 */
void pop_back();			/* 删除链表中的尾元素 */
void pop_front();			/* 删除链表中的首元素 */
int back();					/* 返回链表中尾元素的引用 */
int front();				/* 返回链表中首元素的引用 */

// list容器中定义的成员函数形式的算法
void remove(int x);			/* 调用erase删除掉与x相等的每个元素 */
void sort();				/* 使用<运算符对链表中元素进行排序 */
```



C++中的pair模板支持的操作：

```c++
#include<utility>
std::pair<string, int> p;					/* 创建一个使用默认构造函数进行初始化的pair */
std::pair<string, int> p(v1, v2);          	/* 创建类型为string和int的pair，first成员和seconde成员分别使用v1和v2初始化 */
std::pair<string, int> p{v1, v2};			/* 使用列表初始化，first成员和seconde成员分别使用v1和v2初始化 */
std::pair<string, int>  make_pair(v1, v2); 	/* 返回成员类型为string和int的pair */
p.first										/* 返回first成员的值 */
p.second									/* 返回seconde成员的值*/
```





实现：

```c++
#include <list>
#include <utility>
#include <unordered_map>
using namespace std;

class LRUCache {
private:
    list<pair<int, int>> cache;                             // 使用双向链表保存每个数据，可进行任何位置快速插入删除
    unordered_map<int, list<pair<int, int>>::iterator> m;   // 使用哈希表通过key快速查找到对应的数据的迭代器
    int cap;                                                // LRU缓存的最大容量
public:
    explicit LRUCache(int capacity) {
        cap = capacity;
    }

    /* 获取一个数据的key对应的value, O(1)的时间复杂度, 并将该数据提升为最近访问过的数据 */
    int get(int key) {
        if (m.count(key) == 0) {
            return -1;
        }
        makeRecently(key);
        return m[key]->second;
    }

    /* 插入一个数据(key,val), O(1)的时间复杂度 */
    void put(int key, int value) {
        if (m.count(key) != 0) {
            deleteKey(key);
            addRecently(key, value);
            return;
        }
        if (cap == cache.size()) {
            removeLeastRecently();
        }
        addRecently(key, value);
    }

private:
    /* 将某个key对应的数据，提升为最近使用的 */
    void makeRecently(int key) {
        pair<int, int> data = *m[key];
        cache.erase(m[key]);       // 删除list中迭代器指向的数据
        cache.push_front(data);    // 向list的头部添加一个元素；
        m[key] = cache.begin();
    }

    /* 删除双向链表和哈希表中key对应的数据*/
    void deleteKey(int key) {
        cache.erase(m[key]);    // 删除list中迭代器指向的元素
        m.erase(key);           // 删除map中关键字为key的元素
    }

    /* 以(key,val)键值对, 添加一个数据, 并提升为最近使用的 */
    void addRecently(int key, int val) {
        pair<int, int> data = make_pair(key, val);
        cache.push_front(data);      // list头部插入一个数据
        m[key] = cache.begin();      // map中增加关键字为key的元素
    }

    /* 删除一个最近最少使用的数据，即双向链表中的首元素 */
    void removeLeastRecently() {
        auto data = cache.back();   // 获取list中尾元素的引用
        m.erase(data.first);       	// 删除map中关键字为data.first的元素
        cache.pop_back();           // 删除list中尾元素
    }
};
```

