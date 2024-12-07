#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "RandomInt.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8

    std::unordered_map<std::string, int> myAssets = {
        {"AAPL", 50}, {"GOOGL", 30}, {"MSFT", 20}
    };

    try {
        std::string stock = randomStock(myAssets);
        std::cout << "Randomly selected stock: " << stock << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
