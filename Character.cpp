#include <iostream>
#include <sstream>
#include <stdexcept>
#include "RandomInt.h"
#include "Character.h"
#include "Stage.h"
using namespace std;

const unordered_map<string, int> Character::maxActionCntMap = {
    {"Retail", 5}, {"Rich", 3}, // Player
    {"ShortTerm", 6}, {"LongTerm", 3}, {"Defensive", 4}, {"Insider", 3} // Robot
};

const unordered_map<string, array<int, 2>> Character::initMoneyRangeMap = {
    {"Retail", {4000, 5000}}, {"Rich", {7500, 9000}}, // Player
    {"ShortTerm", {4000, 5500}}, {"LongTerm", {6000, 7000}}, {"Defensive", {6500, 8000}}, {"Insider", {4500, 5500}} // Robot
};

const array<short, 2> Character::tradeLimits = {40, 100};
vector<Skill> Character::skillList = {Foresight(), AssetGrowth(), Hedge(), InsideScoop(), Gamble(), Peek()};

Character::Character(const string& t, const string& n, const string& des) : type(t), name(n), description(des) {
    this->assets.reserve(10); // 最多10種股票
    this->actionCnt = maxActionCntMap.at(this->type);
    this->initMoney = randomInt(initMoneyRangeMap.at(this->type));
    this->currentMoney = this->initMoney;
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
    
    stringstream ss;
    ss << "持有技能：\n";
    for(int i = 0; i < skills.size(); ++i){
        ss << i + 1 << ": " << skills[i]->getName() << '\n';
    }
    return ss.str();
}

string Character::showIntroduction() const {
    // 展示名字、介紹、總資產
    stringstream info; 
    info << "名字： " + this->name + "\n    " + this->description + "\n"; // 縮排四格
    info << "總資產" << this->getTotalAsset() << "\n";
    return info.str();
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
            info << "    " << pair.second.stock->getName() << " X " << pair.second.number << "持股回合數：" << pair.second.roundCnt << "\n";
    }
    info << "總資產：" << this->getTotalAsset() << '\n';
    return info.str();
}

string Character::showActionLog() const {
    if(this->actionLog.empty())
        return "尚無操作紀錄";

    stringstream ss;
    for(const string& record: this->actionLog)
        ss << record << "\n";
}

int Character::tradeStocks(const Stage& stage, const string& ticker, int number, bool isbuy) {
    // 股票代碼與基本數量檢查
    auto stock = stage.stocks.find(ticker);
    if(stock == stage.stocks.end())
        throw invalid_argument("未知的股票代碼：" + ticker);
    if(number <= 0)
        throw invalid_argument("交易量需大於0");

    if (isbuy && number > this->tradeLimit)
        throw invalid_argument("一次最多買入" + to_string(this->tradeLimit) + "張股票");
    else if (!isbuy && number > this->tradeLimit / 2)
        throw invalid_argument("一次最多賣出" + to_string(this->tradeLimit / 2) + "張股票");
    
    // 進入買賣檢查
    int tradeAmount = stock->second->getCurrentPrice() * number;
    if (isbuy) {
        if (this->currentMoney < tradeAmount) 
            throw runtime_error("資金不足無法購買");
        
        // 正式買入
        try {
            // 假設以持有該股
            this->assets.at(ticker).number += number;
        } catch (out_of_range& e) {
            // 未持有該股，將其加入assets中
            this->assets.insert({ticker, Asset(number, stock->second)});
        }
        this->currentMoney -= tradeAmount;

    } else {
        // 賣出
        Asset* myStock; // 需修改其數量，所以用ptr
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
        this->currentMoney += tradeAmount;
    }
    --this->actionCnt;
    string buyOrSell = isbuy ? "買入" : "賣出";
    this->actionLog.push_back(buyOrSell + to_string(number) + "單位的" + ticker);
    return tradeAmount;
}

Result Character::useSkill(Stage& stage, int skillId) {
    Skill* theSkill = this->skills.at(skillId - 1); // may throw out_of_range
    Result result = theSkill->activate(stage, *this);

    this->actionLog.push_back("使用技能：" + theSkill->getName());
    this->skills.erase(this->skills.begin() + skillId - 1);
    --this->actionCnt;
    return result;
}

Player::Player(const string& t, const string& n, const string& des) : Character(t, n, des) {
    this->tradeLimit = Character::tradeLimits[0];
}

void Player::takeAction(Stage& stage, const Round& round) {
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
             << "8: 查看操作紀錄\n"
             << "9: 跳過剩餘操作\n";
        int command;
        cin >> command;
        switch (command) {
            case 1:
                for(Event* e: round.events)
                    e->printEventPartialDetails();
                break;

            case 2: {
                cout << "輸入想查看的角色編號: 1 ~ " << stage.characters.size() << "\n";
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
                    p.second->printStockPartialInfo();
                break;
            }
                
            case 4: {
                if(this->skills.empty())
                    cout << "目前沒有技能\n";
                for(auto* s: this->skills)
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
                    cout << this->useSkill(stage, id).strVal << "\n";
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
                } catch (exception& e) {
                    cerr << e.what() << '\n';
                }
                break;
            }

            case 8: {
                cout << this->showActionLog();
                break;
            }

            case 9: {
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
        cout << "按enter繼續\n";
        cin.ignore(); // ignore'\n'
        string sth;
        getline(cin, sth);
    }
}

Retail::Retail(const string& n, const string& des) : Player("Retail", n, des) {}

Rich::Rich(const string& n, const string& des) : Player("Rich", n, des) {}


// 機器人
Robot::Robot(const string& t, const string& n, const string& des) : Character(t, n, des) {
    this->tradeLimit = Character::tradeLimits[1];
}

template <typename T>
string Robot::randomStock(const unordered_map<string, T>& myAssets) {
    vector<pair<string, T>> a(myAssets.begin(), myAssets.end());
    int index = randomInt(0, a.size() - 1);
    return a[index].first;
}

ShortTerm::ShortTerm(const string& n, const string& des) : Robot("ShortTerm", n, des) {}

vector<string> LongTerm::preferredStocks = {"AAPL", "MSFT", "COST", "KO", "INTC"};

LongTerm::LongTerm(const string& n, const string& des) : Robot("LongTerm", n, des) {
    for(int _ = 0; _ < 3; ++_)
        this->skills.push_back(&Character::skillList[1]);
}

void LongTerm::takeAction(Stage& stage, const Round& round) {
    int curRound = stage.getCurRound();
    if (curRound == 4 || curRound == 8 || curRound == 10)
        this->useSkill(stage, 1);

    while(this->actionCnt > 0 && this->currentMoney > 600) {
        if(this->currentMoney > this->initMoney / 10){
            int num = 15;
            string targetStock = LongTerm::preferredStocks[randomInt(0, preferredStocks.size() - 1)];
            while(true){
                try {
                    this->tradeStocks(stage, targetStock, num, true);
                    break;
                } catch (exception& e) {
                    if(num == 1){
                        break;
                    }
                    else
                        num /= 2;
                }
            }
        } else {
            string target = this->randomStock(this->assets);
            int num = this->assets[target].number / 3;
            this->tradeStocks(stage, target, num, false);
        }
    }
}

const unordered_map<string, vector<string>> Insider::industryToTickers = {
    {"Technology", {"AAPL", "UBER", "MSFT"}},
    {"Biotech", {"MRNA"}},
    {"Consumer Staples", {"KO", "COST"}},
    {"Semiconductor", {"TSM", "INTC"}},
    {"Airlines", {"UAL", "DAL"}}
};

Insider::Insider(const string& ind, const string& n, const string& des) : industry(ind), Robot("Insider", n, des) {
    this->industryStock = Insider::industryToTickers.at(this->industry);
};
