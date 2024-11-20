#ifndef EVENT.H
#define EVENT.H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Event{
private:
    vector<double> affectedStocks; // 用陣列儲存影響個股的權重
    string description; // 事件描述
    int eventImpact; // 事件影響力
    string source; // 事件消息來源
public:
    Event(vector<double> affectedStocks, string description, int eventImpact, string source);


    /*
    influeneStockPrice()
    eventShowup()
    
    */

};

#endif
