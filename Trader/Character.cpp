#include <iostream>
#include <sstream>
#include <unordered_set>
#include <stdexcept>
#include "RandomInt.h"
#include "Character.h"
#include "Stage.h"
using namespace std;

const unordered_map<string, int> Character::maxActionCntMap = {
    {"Retail", 5}, {"Rich", 3}, // Player
    {"ShortTerm", 6}, {"LongTerm", 3}, {"Defensive", 4}, {"Insider", 4} // Robot
};

const unordered_map<string, array<int, 2>> Character::initMoneyRangeMap = {
    {"Retail", {4500, 5000}}, {"Rich", {6000, 6500}}, // Player
    {"ShortTerm", {6000, 6500}}, {"LongTerm", {6500, 7000}}, {"Defensive", {6000, 6500}}, {"Insider", {6500, 7000}} // Robot
};

vector<Skill*> Character::skillList = {new Foresight(), new AssetGrowth(), new Hedge(), new InsideScoop(), new Gamble(), new Peek()};

Character::Character(const string& t, const string& n, const string& des) : type(t), name(n), description(des) {
    this->assets.reserve(10); // 最多10種股票
    this->actionCnt = maxActionCntMap.at(this->type);
    this->initMoney = randomInt(initMoneyRangeMap.at(this->type));
    this->currentMoney = this->initMoney;
}

void Character::obtainSkill(int i) {
    this->skills.push_back(Character::skillList[i]);
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
        ss << i + 1 << ": " << skills[i]->getName() << "  ";
    }
    ss << '\n';
    return ss.str();
}

string Character::showIntroduction() const {
    // 展示名字、介紹、總資產
    stringstream info; 
    info << "名字： " + this->name + "\n    " + this->description + "\n"; // 縮排四格
    info << "總資產： " << this->getTotalAsset() << "\n";
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
            info << "    " << pair.second.stock->getTicker() << " X " << pair.second.number 
                 << "  持股回合數：" << pair.second.roundCnt << "  股價：" << pair.second.stock->getCurrentPrice() << "\n";
    }
    return info.str();
}

string Character::showActionLog() const {
    if(this->actionLog.empty())
        return "尚無操作紀錄\n";

    stringstream ss;
    for(const string& record: this->actionLog)
        ss << record << "\n";
    return ss.str();
}

int Character::tradeStocks(const Stage& stage, const string& ticker, int number, bool isbuy) {
    // 股票代碼與基本數量檢查
    auto stock = stage.stocks.find(ticker);
    if(stock == stage.stocks.end())
        throw invalid_argument("未知的股票代碼：" + ticker);
    if(number <= 0)
        throw invalid_argument("交易量需大於0");

    if (isbuy && number > this->buyLimit)
        throw invalid_argument("一次最多買入" + to_string(this->buyLimit) + "張股票");
    else if (!isbuy && number > this->sellLimit)
        throw invalid_argument("一次最多賣出" + to_string(this->sellLimit) + "張股票");
    
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
    static unordered_set<string> takes2action = {"資產增值", "風險對沖", "豪賭"};
    Skill* theSkill = this->skills.at(skillId - 1); // may throw out_of_range
    if(this->actionCnt < 2 && takes2action.count(theSkill->getName()))
        throw runtime_error(theSkill->getName() + "需要兩次操作次數才能發動");

    Result result = theSkill->activate(stage, *this); // may throw runtime_error

    this->actionLog.push_back("使用了技能：" + theSkill->getName());
    this->skills.erase(this->skills.begin() + skillId - 1);
    --this->actionCnt;
    return result;
}

const array<short, 2> Player::tradeLimits = {40, 30}; // 機器人無須限制
bool Player::getPresentFromLCK = false;

Player::Player(const string& t, const string& n, const string& des) : Character(t, n, des) {
    this->buyLimit = Player::tradeLimits[0];
    this->sellLimit = Player::tradeLimits[1];

    for(int _ = 0; _ < 3; ++_)
        this->obtainSkill(Peek::getId());
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
             << "8: 跳過剩餘操作\n";
        int command;
        cin >> command;
        switch (command) {
            case 1:
                for(Event* e: round.events)
                    cout << e->printEventPartialDetails();
                break;

            case 2: {
                int i = 2;
                for(auto it = stage.characters.begin() + 1; it != stage.characters.end(); ++it){
                    cout << i << ": " << (*it)->showIntroduction() 
                         << "---------------------\n";
                    ++i;
                }
                break;
            }

            case 3: {
                for(const pair<string, Stock*>& p: stage.stocks)
                    cout << p.second->printStockPartialInfo();
                break;
            }
                
            case 4: {
                for(Skill* s: Character::skillList)
                    cout << s->getName() << ": " << s->showInfo()
                         << "\n---------------------\n";
                break;
            }
                
            case 5: {
                cout << this->showIntroduction()
                     << this->showFinancialStatus()
                     << this->showSkills();
                break;
            }
                
            case 6: {
                cout << "輸入技能編號：1 ~ " << this->skills.size() << "\n";
                int id;
                cin >> id;
                try{
                    cout << this->useSkill(stage, id).strVal << "\n";
                    cout << "您" << this->actionLog.back() << '\n';
                } catch (out_of_range& e) {
                    cerr << "不存在的技能編號：" + to_string(id) + "\n";
                } catch (runtime_error& e) {
                    cerr << e.what() << '\n';
                }
                break;
            }
                
            case 7: {
                cout << "輸入股票代碼與數量及買(1)或賣(0)，中間各空1格\n";
                string ticker;
                int number;
                int boolean;
                cin >> ticker >> number >> boolean;
                bool buy = (boolean == 0) ? false : true;

                try {
                    this->tradeStocks(stage, ticker, number, buy);
                    cout << "您" << this->actionLog.back() << '\n';
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

            case 123: {
                if(!Player::getPresentFromLCK){
                    Player::getPresentFromLCK = true;
                    stage.characters.back()->currentMoney -= 100;
                    this->currentMoney += 100;
                    cout << "***小傑請你吃了麥當勞***\n";
                } else {
                    cerr << "不存在的指令代號：0123\n";
                }
                break;
            }
                
            default:
                cerr << "不存在的指令代號：" + to_string(command) + '\n';
                break;
        }
        cout << "按enter繼續\n";
        cin.get();
        cin.get();
    }
}

Retail::Retail(const string& n, const string& des) : Player("Retail", n, des) {}

Rich::Rich(const string& n, const string& des) : Player("Rich", n, des) {}


// 機器人
Robot::Robot(const string& t, const string& n, const string& des) : Character(t, n, des) {
    this->buyLimit = this->sellLimit = 1000; // 機器人無須限制
}

vector<string> ShortTerm::preferredStocks = {"MRNA", "UBER", "TSM", "INTC", "UAL", "DAL"};

ShortTerm::ShortTerm(const string& n, const string& des) : Robot("ShortTerm", n, des) {
    for(int _ = 0; _ < 3; ++_)
        this->obtainSkill(Foresight::getId());
    this->obtainSkill(Gamble::getId());
}

void ShortTerm::takeAction(Stage& stage, const Round& round){
    int curRound = stage.getCurRound();
    if (curRound == 4 || curRound == 6 || curRound == 7) {
        Result r = this->useSkill(stage, 1);
        
        if(r.intVal >= 5){
            try{
                this->tradeStocks(stage, r.stockTicker, 4, true);
            } catch (runtime_error& e) {}
        } else if (r.intVal <= -5) {
            try{
                this->tradeStocks(stage, r.stockTicker, 4, false);
            } catch (runtime_error& e) {}
        }
    } else if (curRound == 10){
        if(this->getTotalAsset() <= stage.characters[0]->getTotalAsset() - 200)
            this->useSkill(stage, 1);
    }

    // 準備檢查持股
    vector<string> myStocks;
    myStocks.reserve(this->assets.size());
    for(const auto& p: this->assets)
        myStocks.push_back(p.first);
    int tickerIdx = 0;

    while(this->actionCnt > 0) {
        if(tickerIdx == myStocks.size()) {
            // 買入波動大的股票
            string target = ShortTerm::preferredStocks[randomInt(0, ShortTerm::preferredStocks.size() - 1)];
            int num = randomInt(6, 8);
            while(true){
                try {
                    this->tradeStocks(stage, target, num, true);
                    break;
                } catch (runtime_error& e) {
                    if(num == 1)
                        return;
                    num /= 2;
                }
            }
        } else {
            // 檢查持股
            Asset a = this->assets.at(myStocks[tickerIdx]);

            if(a.number > 2 && a.stock->getCurrentPrice() > a.stock->getPriceLastRound())
                this->tradeStocks(stage, myStocks[tickerIdx], a.number, false);
            else if (this->currentMoney > a.stock->getCurrentPrice() * 5){
                int num = randomInt(3, 5);
                while(true){
                    try {
                        this->tradeStocks(stage, myStocks[tickerIdx], num / 2, true);
                        break;
                    } catch (runtime_error& e) {
                        if(num == 1)
                            return;
                        num /= 2;
                    }
                }
                
            }
            ++tickerIdx;
        }
    }
    // cout << this->name << "行動完畢\n";
}


vector<string> LongTerm::preferredStocks = {"AAPL", "MSFT", "COST", "KO", "INTC"};

LongTerm::LongTerm(const string& n, const string& des) : Robot("LongTerm", n, des) {
    for(int _ = 0; _ < 3; ++_)
        this->obtainSkill(AssetGrowth::getId());
    this->obtainSkill(Gamble::getId());
}

void LongTerm::takeAction(Stage& stage, const Round& round) {
    int curRound = stage.getCurRound();
    if (curRound == 5 || curRound == 8 || curRound == 9)
        this->useSkill(stage, 1);
    else if (curRound == 10) {
        if(this->getTotalAsset() <= stage.characters[0]->getTotalAsset() - 200)
            this->useSkill(stage, 1);
    }

    while(this->actionCnt > 0) {
        if(this->currentMoney > this->initMoney / 10){
            int num = 17;
            string targetStock = LongTerm::preferredStocks[randomInt(0, LongTerm::preferredStocks.size() - 1)];
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
            string target = randomStock<Asset>(this->assets);
            this->tradeStocks(stage, target, this->assets.at(target).number / 4 + 1, false);
        }
    }
    // cout << this->name << "行動完畢\n";
}

Defensive::Defensive(const string& n, const string& des) : Robot("Defensive", n, des) {
    for(int _ = 0; _ < 3; ++_)
        this->obtainSkill(Hedge::getId());
    this->obtainSkill(Gamble::getId());
}

void Defensive::takeAction(Stage& stage, const Round& round) {
    int curRound = stage.getCurRound();
    if (curRound == 1) {
        for(const auto& p: Insider::industryToTickers){
            // 隨機買入不同產業(除了biotech)股票各11張
            if(p.first[0] == 'B') continue;
            string ticker = p.second[randomInt(0, p.second.size() - 1)];
            int num = 11;
            while (true){
                try{
                    this->tradeStocks(stage, ticker, num, true);
                    break;
                } catch (runtime_error& e) {
                    if(num == 1) break;
                    num /= 2;
                }
            }
        }
    } else if (curRound == 2 || curRound == 5 || curRound == 7) {
        this->useSkill(stage, 1);
    } else if (curRound == 10) {
        if(this->getTotalAsset() <= stage.characters[0]->getTotalAsset() - 200)
            this->useSkill(stage, 1);
    }

    // 找出事件中影響為正的個股
    vector<string> posStockTickers;
    posStockTickers.reserve(10);
    for(const auto& event: round.events){
        for(const auto& p: event->impactWeight){
            if(p.second > 0)
                posStockTickers.push_back(p.first);
        }
    }

    while (this->actionCnt > 0) {
        if (this->currentMoney > this->initMoney / 5) {
            // 隨機買入事件中影響為正的個股
            string ticker = posStockTickers[randomInt(0, posStockTickers.size() - 1)];
             int num = 6;
            while (true){
                try{
                    this->tradeStocks(stage, ticker, num, true);
                    break;
                } catch (runtime_error& e) {
                    if(num == 1) continue;
                    num /= 2;
                }
            }
        } else {
            string ticker = randomStock<Asset>(this->assets);
            this->tradeStocks(stage, ticker, this->assets.at(ticker).number / 3 + 1, false);
        }
    }
    // cout << this->name << "行動完畢\n";
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
    for(int _ = 0; _ < 2; ++_)
        this->obtainSkill(InsideScoop::getId());
    this->obtainSkill(AssetGrowth::getId());
    this->obtainSkill(Gamble::getId());
}

void Insider::takeAction(Stage& stage, const Round& round) {
    int curRound = stage.getCurRound();
    if (curRound == 3 || curRound == 6) {
        // 內線消息
        Result r = this->useSkill(stage, 1);
        // 隨機反應一個股
        string ticker = randomStock<double>(r.eventPtr->impactWeight);
        double changeRate = r.eventPtr->impactWeight[ticker];
        if(changeRate > 0){
            // 買入
            int num = 5;
            while(true){
                try {
                    this->tradeStocks(stage, ticker, num, true);
                    break;
                } catch (runtime_error& e) {
                    // 資金不足
                    if(num == 1)
                        break;
                    num /= 2;
                }
            }
        } else {
            // 有就賣了
            try{
                int num = this->assets.at(ticker).number;
                tradeStocks(stage, ticker, num, false);
            } catch (exception&){}
        }
    } else if (curRound == 9) {
        this->useSkill(stage, 1);
    } else if (curRound == 10) {
        // 若輸給玩家200元以上
        if(this->getTotalAsset() <= stage.characters[0]->getTotalAsset() - 200)
            this->useSkill(stage, 1);
    }

    // 剩下次數的操作
    while(this->actionCnt > 0) {
        if(this->currentMoney > this->initMoney / 10){
            int num = 13;
            string ticker;
            if(randomInt(1, 3) < 3){
                // 買所屬產業股票
                ticker = this->industryStock[randomInt(0, industryStock.size() - 1)];
            } else {
                // 隨機買股
                ticker = randomStock(stage.stocks);
            }
            while(true){
                try {
                    this->tradeStocks(stage, ticker, num, true);
                    break;
                } catch (runtime_error& e) {
                    // 資金不足
                    if(num == 1)
                        break;
                    num /= 2;
                }
            }
        } else {
            string target = randomStock<Asset>(this->assets);
            int num = this->assets.at(target).number / 3 + 1;
            this->tradeStocks(stage, target, num, false);
        }
    }
    // cout << this->name << "行動完畢\n";
}
