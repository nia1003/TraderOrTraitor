#include <iostream>
#include <windows.h>

int main() {
    std::string info = "可用資金： ";

    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8
    std::cout << info;

    return 0;
}
