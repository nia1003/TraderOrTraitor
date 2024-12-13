#include <iostream>
#include <windows.h>
#include <chrono>
#include <random>

using namespace std;

// 隨機整數生成函數
int randomInt(int range1, int range2) {
    // 初始化隨機數引擎
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();   // 用於生成種子
    static std::mt19937 gen(seed); // 隨機數引擎（全局初始化以避免重複構造）

    // 定義均勻分佈
    std::uniform_int_distribution<> distrib(range1, range2);

    // 返回隨機整數
    return distrib(gen);
}

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8

    for(int i = 0; i < 100; ++i){
        cout << randomInt(0, 4);
    }

    return 0;
}
