#include <iostream>
#include <windows.h>
#include "Skill.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8

    cout << sizeof(Skill);

    return 0;
}
