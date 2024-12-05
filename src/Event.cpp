#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Event.h"
#include "Stock.h"

using namespace std;

void Event::printEventDetails() const {
    cout << "事件描述: " << description << endl;
    cout << "影響力: " << eventImpact << endl;
    cout << "消息來源: " << source << endl;

    if (!impactWeight.empty()) {
        cout << "影響範圍與權重: " << endl;
        for (const auto& [ticker, weight] : impactWeight) {
            cout << "  " << ticker << ": " << weight << endl;
        }
    } else {
        cout << "影響範圍: 無" << endl;
    }
}
void Event::printEventPartialDetails() const {
    cout << "事件描述: " << description << endl;
    cout << "消息來源: " << source << endl;
}
// 影響股價的函數
void Event::affectStockPrice(unordered_map<string, Stock>& stockMap) {
    for (auto& [ticker, stock] : stockMap) { // 可能會有衝突
        // 確定這支股票是否受影響
        if (impactWeight.count(ticker)) {
            double weight = impactWeight[ticker];
            int newPrice = stock.getCurrentPrice() *
                                (1 + stock.getSensitivity() * eventImpact * weight);
            int oldPrice = stock.getCurrentPrice();

            // 更新股價
            cout << ticker << "," << stock.getSensitivity() << "," << eventImpact << "," << weight << endl;
            stock.setCurrentPrice(newPrice);
            cout << "Updated " << ticker << " from " << oldPrice
                    << " to new price: " << newPrice << endl;
        }
    }
}