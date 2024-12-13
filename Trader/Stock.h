#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include <string>
#include <vector>
#include "Event.h"

using namespace std;

class Stock{
private:
    string ticker; // 股票的代碼
    string name; // 股票名稱
    string industry; // 產業類別
    int current_price; // 當前價格 = 原始價格 * (1 + 事件敏感度[0.5, 2.0] * 事件影響力[-0.2, 0.2] * 影響權重[0.1, 1.0])
    string description; // 股票描述
    double sensitivity;
    /*
        事件敏感度，0.5 < x <= 2.0
        <1.0：穩定的大型公司（如 TSM, KO）。
        1.0 ~ 2.0：成長型或波動性較大的公司（如 UBER, MRNA）。
    */
    vector<int> priceHistory; // 股票的歷史價格數據，回合結束時更新

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
   int getPriceLastRound() const;
   double getSensitivity() const {return sensitivity;}
   string getTicker() const {return ticker;}
    string getIndustry() { return this->industry; }


   // print股票資訊
   void printStockInfo() const;
   string printStockPartialInfo() const;

// 測試用
void printHistory(){
    cout << this->ticker << ": ";
    for(int& price: this->priceHistory){
        cout << price << " ";
    }
    cout << "\n";
}

   // setter
   void setCurrentPrice(int currentprice) {this->current_price = currentprice;}

friend class Foresight;
};

#endif