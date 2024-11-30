#include <iostream>
#include <windows.h>
#include "Character.h"
#include "Stock.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8

    Player retail("散戶", {0, 500}, 0, "小傑", "作業研究專家");
    cout << retail.showIntroduction();
    cout << retail.showFinancialStatus();

    return 0;
}
