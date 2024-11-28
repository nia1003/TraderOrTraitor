#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
#include "Character.h"
using namespace std;

const int Character::INIT_MONEY = 10000; // 暫定，全角色共享同樣的值
int Character::currentId = 0;

Character::Character(const string& n, const string& des) : name(n), description(des) {
    this->currentMoney = Character::INIT_MONEY; // to be added by Child's initBonus
    this->id = Character::currentId++;
    this->assets.reserve(10);
    this->tradeLog.reserve(20);
}

int Character::getTotalAsset() const {
    int total = this->currentMoney;
    for (int i = 0; i < assets.size(); ++i) {
        total += assets[i].getValue();
    }
    return total;
}

string Character::showIntroduction() const {
    // 展示身分、名字、介紹，身分由各子類加入
    string info = "名字： " + this->name + "\n    " + this->description; // 縮排四格
    return info;
}

string Character::showFinancialStatus() const {
    // 展示currentMoney、assets
    stringstream info;
    info << "可用資金： " << this->currentMoney << "\n持有股票： ";

    const int& assetCnt = assets.size();
    if (assetCnt == 0)
        info << "未持有任何股票\n";
    else {
        info << '\n';
        for(int i = 0; i < this->assets.size(); ++i) 
            info << "    " << assets[i].stock->getName() << " X " << assets[i].number << "\n";
    }
    return info.str();
}

// 隨機整數生成函數
int randomInt(const array<short, 2>& range) {
    // 初始化隨機數引擎
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();   // 用於生成種子
    static std::mt19937 gen(seed); // 隨機數引擎（全局初始化以避免重複構造）

    // 定義均勻分佈
    std::uniform_int_distribution<> distrib(range[0], range[1]);

    // 返回隨機整數
    return distrib(gen);
}

Player::Player(const string& iden, const array<short, 2>& range, int cntAdjust,  const string& n, const string& des)
 : identity(iden), initBonusRange(range), tradeCntAdjust(cntAdjust), Character(n, des) {
    this->currentMoney += randomInt(this->initBonusRange);
}

string Player::showIntroduction() const {
    string info = "身分： " + this->identity + " ";
    info += Character::showIntroduction() + "\n";
    return info;
}