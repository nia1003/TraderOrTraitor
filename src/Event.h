#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Event{
private:
    unordered_map<string, double> impactWeight; 
    /* 
        用unordered_map儲存影響個股的權重
        權重通常應介於0.0-2.0之間
        2為最大，代表有重大影響
    */
    string description; // 事件描述
    int eventImpact; 
    /* 
        事件影響力，用正負號來決定，-20 <= x <= 10
        正負來判斷是正面還是負面
    */
    string source; // 事件消息來源
public:
    Event(unordered_map<string, double> impactWeight, string description, int eventImpact, string source)
    : impactWeight(impactWeight), description(description), eventImpact(eventImpact), source(source) {} ;


    /* 可能會用到的成員函數
    influeneStockPrice()
    eventShowup()
    
    */

   // print事件資訊
   void printEventDetails() const;

};
// ---成員函數---
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
#endif
