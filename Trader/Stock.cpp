#include <iostream>
#include <sstream>
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
string Stock::printStockPartialInfo() const
{
    stringstream ss;
    ss << "股票資訊:" << endl
       << "------------------" << endl
       << "股票ID: " << ticker << endl
       << "股票名稱: " << name << endl
       << "產業類別: " << industry << endl
       << "目前價格: $" << current_price << endl
       << "個股描述: " << description << endl;

    if (!priceHistory.empty()) {
        ss << "價格歷史: ";
        for (size_t i = 0; i < priceHistory.size(); ++i) {
            ss << priceHistory[i];
            if (i != priceHistory.size() - 1) ss << ", ";
        }
        ss << endl;
    } else {
        ss << "Price History: No data available yet." << endl;
    }

    ss << "------------------" << endl;
    return ss.str();
}
void Stock::addToPriceHistory(int current_price) // 回合結束的時候更新
{
    priceHistory.push_back(current_price);
}
int Stock::getPriceLastRound() const
{
    // 如果歷史價格不足兩個，返回當前價格或預設值
    if(priceHistory.empty())
    {
        return current_price;
    }

    // 返回倒數第1個價格
    return priceHistory.back();
}