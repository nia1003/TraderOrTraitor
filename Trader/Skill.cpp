#include "Skill.h"
#include "RandomInt.h"
#include <unordered_set>
#include <stdexcept>
using namespace std;

Result Foresight::activate(Stage& stage, Character& cha) const {
    int curRound = stage.getCurRound();
    if(curRound == 10){
        int increment = cha.getTotalAsset() * 0.01;
        cha.currentMoney += increment;
        return Result("第十回合使用，轉為獲得" + to_string(increment));
    }
    // 隨機找個股，查看其價格陣列
    string ticker = randomStock(stage.stocks);
    int nextPrice = Stage::price_per_round.at(ticker)[curRound + 1];
    int curPrice = Stage::price_per_round.at(ticker)[curRound];
    
    double changeRate = static_cast<double>(nextPrice) / curPrice;
    int rate = round(changeRate * 100) - 100;
    return Result(ticker + "在下回合將迎來" + to_string(rate) + "%的價格變動", changeRate, nullptr, ticker);
}

Result AssetGrowth::activate(Stage& stage, Character& cha) const {
    if(cha.assets.empty())
        throw runtime_error("您未持有任何股票，無法使用" + this->getName());

    int maxRoundCnt = 0;
    Asset theAsset(0, stage.stocks["AAPL"]);

    // 找最久的持股，如果一樣，就找出總價值高的
    for (const auto& a: cha.assets) {
        if(a.second.roundCnt > maxRoundCnt){
            maxRoundCnt = a.second.roundCnt;
            theAsset = a.second;
        } else if (a.second.roundCnt == maxRoundCnt && a.second.getValue() > theAsset.getValue()){
            theAsset = a.second;
        }
    }

    if(maxRoundCnt >= 7) {
        int increment = theAsset.getValue() * 0.16;
        cha.currentMoney += increment;
        return Result("最久的持股為" + theAsset.stock->getTicker() + "，獲得" + to_string(increment) + "的資金");
    } else if(maxRoundCnt >= 3) {
        int num = theAsset.number;
        while(true){
            if(cha.isPlayer()){
                cout << "最久的持股： " << theAsset.stock->getTicker() << "\n輸入欲購買數量：";
                cin >> num;
            }
            try {
                int reward = cha.tradeStocks(stage, theAsset.stock->getTicker(), num, true) * 0.08;
                cha.currentMoney += reward;
                break;
            } catch (exception& e) {
                if(cha.isPlayer())
                    cerr << e.what() << "\n";
                else {
                    if(num == 1)
                        cha.currentMoney += theAsset.stock->getCurrentPrice();
                    else 
                        num /= 2;
                }
            }
        }
    } else {
        return Result("沒有持股超過3回合的股票");
    }
}

Result Hedge::activate(Stage& stage, Character& cha) const {
    if(cha.assets.empty())
        throw runtime_error("您未持有任何股票，無法使用" + this->getName());

    // 找出持股產業數量，算出倍率
    unordered_set<string> industrySet;
    for(const auto& p: cha.assets){
       industrySet.insert(p.second.stock->getIndustry());
    }
    int magification = (industrySet.size() - 1 < 3) ? industrySet.size() - 1 : 3;

    // 進行交易
    int money;
    string ticker;
    if(cha.isPlayer()){
        while(true){
            cout << "輸入欲賣出的股票代碼與數量，中間空1格\n";
            int number;
            cin >> ticker >> number;

            try {
                money = cha.tradeStocks(stage, ticker, number, false);
                break;
            } catch (exception& e) {
                cerr << e.what() << '\n';
            }
        }
    } else {
        // 找到持股中最有價值資產，賣2/3
        int value = 0;
        Asset maxAsset(0, stage.stocks["AAPL"]); // 僅表示0價值資產
        for (const auto& a: cha.assets) {
            if(a.second.getValue() > value){
                value = a.second.getValue();
                maxAsset = a.second;
            }
        }
        ticker = maxAsset.stock->getTicker();
        money = cha.tradeStocks(stage, ticker, maxAsset.number * 2 / 3 + 1, false);
    }

    // 判斷是否為跌價股
    Stock* theStock = stage.stocks.at(ticker);
    if(theStock->getCurrentPrice() < theStock->getPriceLastRound()){
        int increment = money * magification * 0.04;
        cha.currentMoney += increment;
        return Result("賣出跌價股，獲得" + to_string(increment) + "的額外收益");
        
    } else {
        int increment = money * magification * 0.02;
        cha.currentMoney += increment;
        return Result("賣出增值或等值股，獲得" + to_string(increment) + "的額外收益");
    }
}

Result InsideScoop::activate(Stage& stage, Character& cha) const {
    int curRound = stage.getCurRound();
    if(curRound == 10){
        int increment = cha.getTotalAsset() * 0.01;
        cha.currentMoney += increment;
        return Result("第十回合使用，轉為獲得" + to_string(increment));
    }

    // 正式找到下回合事件
    vector<Event*>& events = stage.rounds[curRound].events;
    int eventId =  randomInt(0, events.size() - 1);
    return Result(events[eventId]->description, -100, events[eventId]);
}

Result Gamble::activate(Stage& stage, Character& cha) const {
    if(cha.assets.empty())
        throw runtime_error("您未持有任何股票，無法使用" + this->getName());

    int money;
    if(cha.isPlayer()){
        while(true){
            cout << "輸入欲賣出的股票代碼與數量，中間空1格\n";
            string ticker;
            int number;
            cin >> ticker >> number;

            try {
                money = cha.tradeStocks(stage, ticker, number, false);
                break;
            } catch (exception& e) {
                cerr << e.what() << '\n';
            }
        }
    } else {

        // 電腦操作，找到最有價值資產，全賣光
        Asset maxAsset(0, stage.stocks.at("AAPL")); // 僅表示0價值資產
        for (const auto& a: cha.assets) {
            if(a.second.getValue() > maxAsset.getValue()){
                maxAsset = a.second;
            }
        }
        money = cha.tradeStocks(stage, maxAsset.stock->getTicker(), maxAsset.number, false);
    }
    
    // 決定成敗
    int result = randomInt(1, 10);
    int moneyChange;
    if(result <= 6){
        // 成功
        moneyChange = money * 0.25;
        cha.currentMoney += moneyChange;
        return Result("豪賭成功！獲得" + to_string(moneyChange) + "的額外收益");
    } else {
        // 失敗
        moneyChange = money * 0.12;
        cha.currentMoney -= moneyChange;
        return Result("豪賭失敗，承擔" + to_string(moneyChange) + "的虧損");
    }
}

Result Peek::activate(Stage& stage, Character& cha) const {
    // 玩家特有技能
    while(true){
        cout << "輸入想查看的角色編號: 2 ~ " << stage.characters.size() << "\n";
        int id;
        cin >> id;
        try{
            Character* she = stage.characters.at(id - 1);
            return Result(she->showIntroduction() + 
                    she->showFinancialStatus() +
                    she->showActionLog());
        } catch (out_of_range& e) {
            cerr << "不存在的角色編號：" + to_string(id) + "\n";
        }
    }
}
