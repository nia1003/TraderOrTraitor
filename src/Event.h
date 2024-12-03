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
        權重通常應介於-1.0-1.0之間
        |0.0| ~ |0.3|：間接影響（如整體市場波動）。
        |0.3| ~ |0.7|：中等影響（如科技行業新聞）。
        |0.7| ~ |1.0|：重大影響（如直接關聯的個股新聞）。
    */
    string description; // 事件描述
    int eventImpact; 
    /* 
        [0, 0.2]
        單純處理事件影響力，正面負面交由個股來判斷
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
