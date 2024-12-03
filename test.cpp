#include <iostream>
#include <windows.h>
#include "RandomInt.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8

    for(int i = 0; i < 10; ++i)
        cout << randomInt(0, 100) << " ";

    return 0;
}
