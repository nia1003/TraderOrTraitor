#include "Market.h"
#include <cstdlib>
#include <ctime>


Stock::Stock(const std::string& name, double price)
    : name(name), price(price) {}

void Stock::updatePrice() {
    // 模擬價格隨機變動（例如：-5% 到 +5% 之間）
    double changePercent = ((rand() % 101) - 50) / 100.0; // -0.5 到 0.5
    price += price * changePercent;
    if (price < 1) price = 1; // 確保價格不低於 1
}

Market::Market() {
    // 初始化一些股票
    stocks.push_back(Stock("AAPL", 150.0));
    stocks.push_back(Stock("GOOGL", 2800.0));
    stocks.push_back(Stock("TSLA", 700.0));
    srand(static_cast<unsigned int>(time(0))); // 初始化隨機數種子
}

void Market::updateMarket() {
    for (auto& stock : stocks) {
        stock.updatePrice();
    }
}

Stock* Market::findStock(const std::string& name) {
    for (auto& stock : stocks) {
        if (stock.name == name) {
            return &stock;
        }
    }
    return nullptr;
}
