#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
// #include <Stock.h>
class Stock{};
using namespace std;

class Character{
protected:
    static const int INIT_MONEY;
    // static const string IDENTITY; // e.g. 散戶、富二代
    // 身分相關
    short id; // served as key
    string name;
    string description;
    string info; // 展示currentMoney、stocks等資訊

    // 功能相關
    int initBonus; // 可能設計成高基礎值多少
    int currentMoney;
    vector<Stock*> stocks;
    vector<string> tradeLog; // 交易紀錄

public:
    // constructors and getters
    Character() {}
    int getCurrentMoney() const;
    string getName() const;
    // get identity() const
    string getDesciption() const;
    int getTotalAsset() const; // currentMoney + Σ(s.num * s.price) for s in stocks

    // 遊戲操作相關
    template <typename T> // 名字或id(也可統一某一個)
    void tradeStocks(const T& stockId, const int number); // number大於0表示買入，小於0表示賣出
    template <typename T>
    string seeOthersInfo(const T& characterId); // 展示角色資訊
};

const int Character::INIT_MONEY = 10000; // 暫定，全角色共享同樣的值

// 散戶(玩家主要操作角色)
class Retail : public Character{
private:
    static const string IDENTITY;
};

const string Retail::IDENTITY = "??????";

#endif // CHARACTER_H
