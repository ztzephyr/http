//
// Created by 86380 on 2023/2/9.
//

#ifndef PRO1_TEST_DESIGN_H
#define PRO1_TEST_DESIGN_H

#include<iostream>
#include <string>
#include <unordered_map>


using namespace std;

// 设计生成验证码的系统
class AuthenticationManager {
public:

    int liveTime; // 验证码有效时长

    unordered_map<string, int> m; // 记录验证码tokenId及失效时刻

    AuthenticationManager(int timeToLive) {
        liveTime = timeToLive;
    }

    void generate(string tokenId, int currentTime) {
        m[tokenId] = currentTime + liveTime;
    }

    void renew(string tokenId, int currentTime) {
        if (m[tokenId] < currentTime) {
            return;
        }
        m[tokenId] = currentTime;
    }

    int countUnexpiredTokens(int currentTime) {
        int res = 0;
        for ( auto it : m ) {
            if ( it.second < currentTime) {
                res++;
            }
        }
        return res;
    }
};













































#endif //PRO1_TEST_DESIGN_H
