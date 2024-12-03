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