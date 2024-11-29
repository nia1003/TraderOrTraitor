#include <iostream>
#include <windows.h>
#include "Character.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8
    
    string name = "小傑";
    string intro = "資管系副教授";
    Retail re(name, intro);

    cout << re.showIntroduction();
    cout << re.showFinancialStatus();

    Stock s;
    s.name = "IM股";
    s.price = 100;
    Asset a(5, &s);
    re.addAsset(a);
    cout << re.showFinancialStatus();
    cout << "總資產： " << re.getTotalAsset();
}