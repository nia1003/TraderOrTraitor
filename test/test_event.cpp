#include <iostream>
#include <vector>
#include "Event.h"
#include "stock.h"
using namespace std;

int main() {
    // 構建影響權重的 unordered_map
    unordered_map<string, double> weights = {
        {"Apple", 1.5},
        {"Microsoft", 1.2},
        {"Tesla", 2.0}
    };

    // 建立 Event 物件
    Event Crises(weights, "Technology Market Disruption", 10, "Global News");

    // 打印事件資訊
    Crises.printEventInfo();

    return 0;
}