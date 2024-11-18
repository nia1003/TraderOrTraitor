#ifndef STOCK_H
#define STOCK_H

#include <iostream>
#include <string>
#include <vector>


class Stock{
private:
    int stockID; // 股票的代碼
    std::string name; // 股票名稱
    std::string industry; // 個股事件、產業事件、總體事件
    double current_price; // 當前價格
    std::string description; // 股票描述
    double volatility; // 股票波動率
    double sensitivity; // 事件敏感度
    std::vector<double> priceHistory; // 股票的歷史價格數據，回合結束時更新

public:
    Stock(int id, const std::string& name, const std::string& industry, double price, const std::string& description, double volatility, double sensitivity);

    ~Stock();

    /*
        upDatePriceHistory()
    */

};

#endif