#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Event{
private:
    /* 
    在想要不要用unordered_map儲存
    像這樣 unordered_map<int, double> affectedStocks
    寫起來會比較直觀affectedStocks[101] = 0.5;
    */
    vector<double> affectedStocks; // 用陣列儲存影響個股的權重
    string description; // 事件描述
    int eventImpact; // 事件影響力
    string source; // 事件消息來源
public:
    Event(vector<double> affectedStocks, string description, int eventImpact, string source)
    : affectedStocks(affectedStocks), description(description), eventImpact(eventImpact), source(source) {} ;


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

    if (!affectedStocks.empty()) {
        cout << "Affected Stocks Weights: ";
        for (size_t i = 0; i < affectedStocks.size(); ++i) {
            cout << affectedStocks[i];
            if (i != affectedStocks.size() - 1) cout << ", ";
        }
        cout << endl;
    } else {
        cout << "Affected Stocks Weights: No data available yet." << endl;
    }

    cout << "------------------" << endl;
}
#endif
