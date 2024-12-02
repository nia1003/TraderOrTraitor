#include <iostream>
#include <sstream>
#include <stdexcept>
#include "RandomInt.h"
#include "Character.h"
#include "Stage.h"
using namespace std;

constexpr short MAX_BUY_CNT = 50;
constexpr short MAX_SELL_CNT = 25;

int Character::currentId = 0;

Character::Character(const string& n, const string& des) : name(n), description(des) {
    this->id = Character::currentId++;
    this->assets.reserve(10); // 最多10種股票
}

int Character::getTotalAsset() const {
    int total = this->currentMoney;
    for (const auto& pair: this->assets) {
        total += pair.second.getValue();
    }
    return total;
}

string Character::showSkills() const {
    if(this->skills.empty())
        return "目前沒有技能\n";
    
    "持有技能：";
    for(int i = 0; i < skills.size(); ++i){
        skills[i]->getName();
        cout << ',';
    }
    return "\n";
}

string Character::showIntroduction() const {
    // 展示身分、名字、介紹，身分由各子類加入
    string info = "名字： " + this->name + "\n    " + this->description + "\n"; // 縮排四格
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
        for(const auto& pair: this->assets) 
            info << "    " << pair.second.stock->getName() << " X " << pair.second.number << "\n";
    }
    info << "總資產：" << this->getTotalAsset() << '\n';
    return info.str();
}

void Character::tradeStocks(const Stage& stage, const string& ticker, int number, bool isbuy) {
    // 股票代碼與基本數量檢查
    auto stock = stage.stocks.find(ticker);
    if(stock == stage.stocks.end())
        throw invalid_argument("未知的股票代碼：" + ticker);
    if(number <= 0)
        throw invalid_argument("交易量需大於0");

    if (isbuy && number > MAX_BUY_CNT)
        throw invalid_argument("一次最多買入" + to_string(MAX_BUY_CNT) + "張股票");
    else if (!isbuy && number > MAX_SELL_CNT)
        throw invalid_argument("一次最多賣出" + to_string(MAX_SELL_CNT) + "張股票");
    
    // 進入買賣檢查
    if (isbuy) {
        int cost = stock->second->getCurrentPrice() * number;
        if (this->currentMoney < cost) 
            throw runtime_error("資金不足無法購買");
        
        // 正式買入
        try {
            // 假設以持有該股
            this->assets.at(ticker).number += number;
        } catch (out_of_range& e) {
            // 未持有該股，將其加入assets中
            this->assets.insert({ticker, Asset(number, stock->second)});
        }
        this->currentMoney -= cost;

    } else {
        // 賣出
        Asset* myStock; // 需修改其值，所以用ptr
        try {
            // 假設以持有該股
            myStock = &this->assets.at(ticker);
        } catch (out_of_range& e) {
            throw runtime_error("未持有該項股票");
        }
        if (number > myStock->number)
            throw runtime_error("賣出數量大於持有數量");

        // 正式賣出
        myStock->number -= number;
        if(myStock->number == 0)
            this->assets.erase(ticker);
        this->currentMoney += stock->second->getCurrentPrice() * number;
    }
}

void Player::takeAction(const Stage& stage, const Round& round) {
    while (this->actionCnt > 0) {
        cout << "剩餘操作次數：" << this->actionCnt << '\n';
        cout << "輸入操作指令\n"
             << "1: 查看事件內容\n"
             << "2: 查看其他角色基本資訊\n"
             << "3: 查看股票資訊\n"
             << "4: 查看技能效果\n"
             << "5: 查看自身資訊\n"
             << "6: 使用技能(消耗操作次數)\n"
             << "7: 交易股票(消耗操作次數)\n"
             << "8: 跳過剩餘操作\n";
        int command;
        cin >> command;
        switch (command) {
            case 1:
                for(Event* e: round.events)
                    e->printEventInfo();
                break;

            case 2: {
                cout << "輸入角色編號\n";
                int id;
                cin >> id;
                try{
                    cout << stage.characters.at(id - 1)->showIntroduction();
                } catch (out_of_range& e) {
                    cerr << "不存在的角色編號：" + to_string(id) + "\n";
                }
                break;
            }

            case 3: {
                for(const pair<string, Stock*>& p: stage.stocks)
                    p.second->printStockInfo();
                break;
            }
                
            case 4: {
                if(this->skills.empty())
                    cout << "目前沒有技能\n";
                for(Skill* s: this->skills)
                    s->showInfo();
                break;
            }
                
            case 5: {
                cout << this->showIntroduction()
                     << this->showFinancialStatus()
                     << this->showSkills();
                break;
            }
                
            case 6: {
                cout << "輸入技能編號\n";
                int id;
                cin >> id;
                try{
                    Skill& theSkill = *this->skills.at(id - 1);
                    theSkill.activate();
                    --this->actionCnt;
                    this->actionLog.push_back("使用技能：" + theSkill.getName());
                } catch (out_of_range& e) {
                    cerr << "不存在的技能編號：" + to_string(id) + "\n";
                }
                break;
            }
                
            case 7: {
                cout << "輸入股票編號與數量及買(1)或賣(0)，中間各空1格\n";
                string ticker;
                int number;
                int boolean;
                cin >> ticker >> number >> boolean;
                bool buy = (boolean == 0) ? false : true;

                try {
                    this->tradeStocks(stage, ticker, number, buy);
                    --this->actionCnt;
                    string buyOrSell = buy ? "買入" : "賣出";
                    this->actionLog.push_back(buyOrSell + to_string(number) + "單位的" + ticker);
                } catch (exception& e) {
                    cerr << e.what() << '\n';
                }
                break;
            }

            case 8: {
                cout << "是否確定跳過操作? (輸入Y表示確定)\n";
                char yes;
                cin >> yes;
                if(yes == 'y' || yes == 'Y')
                    this->actionCnt = 0;
                continue; // 回到while迴圈後，立刻觸發終止條件
            }
                
            default:
                cerr << "不存在的指令代號：" + to_string(command);
                break;
        }
        cout << "輸入任意文字或按enter繼續\n";
        cin.ignore(); // ignore'\n'
        string sth;
        getline(cin, sth);
    }
}

const int Retail::maxActionCnt = 6;
const array<int, 2> Retail::initMoneyRange = {4000, 5500};

Retail::Retail(const string& n, const string& des) : Player(n, des) {
    this->actionCnt = Retail::maxActionCnt;
    this->currentMoney = randomInt(Retail::initMoneyRange);
}

const int Rich::maxActionCnt = 3;
const array<int, 2> Rich::initMoneyRange = {7500, 9000};

Rich::Rich(const string& n, const string& des) : Player(n, des) {
    this->actionCnt = Rich::maxActionCnt;
    this->currentMoney = randomInt(Rich::initMoneyRange);
}
