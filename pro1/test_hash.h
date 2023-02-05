//
// Created by 86380 on 2023/2/1.
//

#ifndef PRO1_TEST_HASH_H
#define PRO1_TEST_HASH_H


#include <string>
#include<unordered_map>


using namespace std;

class S2325 {
public:
    string decodeMessage(string key, string message) {
        unordered_map<char, char> m;
        char v = 'a';
        for (auto c : key) {
            if (c != ' ' && m.count(c) == 0) {
                m[c] = v++;  // 记录实际字符...
            }
        }
        for (auto &s : message) {
            if (s != ' ') {
                s = m[s];   // 替换为实际字符...
            }
        }
        return message;
    }
};









#endif //PRO1_TEST_HASH_H
