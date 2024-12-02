#ifndef RANDOM_INT_H
#define RANDOM_INT_H

#include <chrono>
#include <random>
#include <array>
using namespace std;

// 隨機整數生成函數
int randomInt(const array<int, 2>& range) {
    // 初始化隨機數引擎
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();   // 用於生成種子
    static std::mt19937 gen(seed); // 隨機數引擎（全局初始化以避免重複構造）

    // 定義均勻分佈
    std::uniform_int_distribution<> distrib(range[0], range[1]);

    // 返回隨機整數
    return distrib(gen);
}

int randomInt(int min, int max) {
    array<int, 2> range = {min, max};
    return randomInt(range);
}

#endif