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
    for (auto& p : stockMap) { // 可能會有衝突
        // 確定這支股票是否受影響
        if (impactWeight.count(p.first)) {
            double weight = impactWeight[p.first];
            int newPrice = p.second.getCurrentPrice() *
                                (1 + p.second.getSensitivity() * eventImpact * weight);
            int oldPrice = p.second.getCurrentPrice();

            // 更新股價
            cout << p.first << "," << p.second.getSensitivity() << "," << eventImpact << "," << weight << endl;
            p.second.setCurrentPrice(newPrice);
            // cout << "Updated " << p.first << " from " << oldPrice
            //         << " to new price: " << newPrice << endl;
        }
    }
}