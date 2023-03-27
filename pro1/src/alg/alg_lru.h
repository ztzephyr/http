#ifndef PRO1_LRU_H
#define PRO1_LRU_H

#include <list>
#include <utility>                                          // pair类型在该头文件中
#include <unordered_map>

using namespace std;

/* LRU缓存数据结构设计 */
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
        cache.push_front(data);         // 向list的头部添加一个元素；
        m[key] = cache.begin();
    }

    /* 删除双向链表和哈希表中key对应的数据*/
    void deleteKey(int key) {
        cache.erase(m[key]);    // 删除list中迭代器指向的元素
        m.erase(key);                // 删除map中关键字为key的元素
    }

    /* 以(key,val)键值对, 添加一个数据, 并提升为最近使用的 */
    void addRecently(int key, int val) {
        pair<int, int> data = make_pair(key, val);
        cache.push_front(data);      // list头部插入一个数据
        m[key] = cache.begin();         // map中增加关键字为key的元素
    }

    /* 删除一个最近最少使用的数据，即双向链表中的首元素 */
    void removeLeastRecently() {
        auto data = cache.back();   // 获取list中尾元素的引用
        m.erase(data.first);               // 删除map中关键字为data.first的元素
        cache.pop_back();                    // 删除list中尾元素
    }
};


























#endif //PRO1_LRU_H
