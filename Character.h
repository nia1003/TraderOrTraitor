#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <Stock.h>
using namespace std;

class Character{
protected:
    // 身分相關
    short id;
    string identity; // 或直接用數字表示身分
    string name;
    string description;

    // 功能相關
    int initBonus; // 可能設計成高基礎值多少
    int currentMoney;
    vector<Stock> stocks;

public:
    int getCurrentMoney();
    string getName();
    // get identity
    string getDesciption();
    int getTotalAsset(); // currentMoney + Σ(s.num * s.price) for s in stocks
};

#endif // CHARACTER_H
