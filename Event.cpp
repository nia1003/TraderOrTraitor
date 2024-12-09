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
        for (const auto& p : impactWeight) {
            cout << "  " << p.first << ": " << p.second << endl;
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
void Event::affectStockPrice(unordered_map<string, Stock*>& stockMap) {
    for (auto& p : stockMap) {
        // 確認該股票是否受影響
        if (impactWeight.count(p.first)) {
            double weight = impactWeight[p.first];

            // 使用指標訪問 p.second 成員
            double sensitivity = p.second->getSensitivity();
            int oldPrice = p.second->getCurrentPrice();

            // 根據公式計算新價格
            int newPrice = oldPrice * (1 + sensitivity * eventImpact * weight);

            // 更新股價
            p.second->setCurrentPrice(newPrice);

            // Debug 輸出
        }
    }
}
