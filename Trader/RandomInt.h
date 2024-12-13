#ifndef RANDOM_INT_H
#define RANDOM_INT_H

#include <chrono>
#include <random>
#include <array>
#include <unordered_map>
using namespace std;

// 隨機整數生成函數
int randomInt(const array<int, 2>& range);
int randomInt(int min, int max);

// 隨機找到股票代碼
template <typename T>
string randomStock(const unordered_map<string, T>& myAssets) {
    auto it = myAssets.begin();
    advance(it, randomInt(0, myAssets.size() - 1));
    return it->first;
}

#endif