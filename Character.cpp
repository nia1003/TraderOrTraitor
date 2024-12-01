#include <iostream>
#include <sstream>
#include <stdexcept>
#include "RandomInt.h"
#include "Character.h"
using namespace std;

int Character::currentId = 0;

Character::Character(const string& n, const string& des) : name(n), description(des) {
    this->id = Character::currentId++;
    this->assets.reserve(10);
    this->actionLog.reserve(20);
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

