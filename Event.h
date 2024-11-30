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
   void printEventInfo() const;

};
// ---成員函數---
void Event::printEventInfo() const {
    cout << "Event Information:" << endl;
    cout << "------------------" << endl;
    cout << "Description: " << description << endl;
    cout << "Impact: " << eventImpact << endl;
    cout << "Source: " << source << endl;

    // 檢查是否有數據
    if (!impactWeight.empty()) {
        cout << "Affected Stocks Weights: ";
        size_t count = 0; // 計數器用於判斷是否是最後一個元素
        for (const auto& pair : impactWeight) {
            cout << pair.first << " (" << pair.second << ")";
            if (++count != impactWeight.size()) cout << ", "; // 如果不是最後一個，添加逗號
        }
        cout << endl;
    } else {
        cout << "Affected Stocks Weights: No data available yet." << endl;
    }

    cout << "------------------" << endl;
}
#endif