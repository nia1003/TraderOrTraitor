#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Event.h"
#include "Stock.h"

using namespace std;

void Stock::printStockInfo() const
{
    cout << "股票資訊:" << endl;
    cout << "------------------" << endl;
    cout << "股票ID: " << ticker << endl;
    cout << "股票名稱: " << name << endl;
    cout << "產業類別: " << industry << endl;
    cout << "目前價格: $" << current_price << endl;
    cout << "個股描述: " << description << endl;
    cout << "事件敏感度: " << sensitivity << endl;

    if (!priceHistory.empty()) {
        cout << "價格歷史: ";
        for (size_t i = 0; i < priceHistory.size(); ++i) {
            cout << priceHistory[i];
            if (i != priceHistory.size() - 1) cout << ", ";
        }
        cout << endl;
    } else {
        cout << "Price History: No data available yet." << endl;
    }

    cout << "------------------" << endl;
}
void Stock::addToPriceHistory(int current_price)
{
    priceHistory.push_back(current_price);
}