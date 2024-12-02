#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Stock{
private:
    string ticker; // 股票的代碼
    string name; // 股票名稱
    string industry; // 產業類別
    int current_price; // 當前價格 = 原始價格 * 事件敏感度 * 事件影響力 * 影響權重
    string description; // 股票描述
    double sensitivity;
    /*
        事件敏感度，0.0 < x <= 2.0
        1以上代表偏敏感
        1以下代表受事件影響的範圍有限，大型股的特質
    */
    vector<double> priceHistory; // 股票的歷史價格數據，回合結束時更新

public:
    Stock(string ticker, const string& name, const string& ind, int price, const string& des, double sen) : 
    ticker(ticker), name(name), industry(ind), current_price(price), description(des), sensitivity(sen), priceHistory(0) {;}

    // ~Stock();

    
    /*可能會用到的成員函數
    updateCurrentPrice()
    */

   // 更新歷史價格
    void addToPriceHistory(int current_price);

   // getter
   double getCurrentPrice() const {return current_price;}

   // print股票資訊
   void printStockInfo() const;

};
// ---成員函數---
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

#endif