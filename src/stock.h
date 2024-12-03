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
    int current_price; // 當前價格 = 原始價格 + 事件敏感度[0.5, 2.0] * 事件影響力[-0.5, 0.5] * 影響權重[0.0, 1.0]
    string description; // 股票描述
    double sensitivity;
    /*
        事件敏感度，0.5 < x <= 2.0
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
   int getCurrentPrice() const {return current_price;}

   // print股票資訊
   void printStockInfo() const;

    // setter
    void setCurrentPrice(int currentprice) {this->current_price = currentprice;}
};

#endif