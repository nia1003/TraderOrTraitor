#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "RandomInt.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8

    double d = 123.456789;
    cout << to_string(round(d * 100) / 100);

    return 0;
}
