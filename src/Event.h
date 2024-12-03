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
        權重通常應介於0.0-1.0之間
        2為最大，代表有重大影響
    */
    string description; // 事件描述
    int eventImpact; 
    /* 
        事件影響力，用正負號來決定，-0.5 <= x <= 0.5
        正負來判斷是正面還是負面
    */
    string source; // 事件消息來源
public:
    Event(unordered_map<string, double> impactWeight, string description, int eventImpact, string source)
    : impactWeight(impactWeight), description(description), eventImpact(eventImpact), source(source) {} ;

    // print事件資訊
    void printEventDetails() const;

    // 影響股價的函數
    void affectStockPrice();
    /*
    抓出股價的
    
    */
};

#endif
