#include "Stage.h"
#include "RandomInt.h"
#include <algorithm>

const unordered_map<string, array<int, 11>> Stage::price_per_round = 
{
    {"AAPL", {150, 159, 114, 127, 133, 184, 174, 177, 177, 206, 206}},
    {"MSFT", {280, 290, 209, 233, 241, 308, 286, 280, 269, 314, 314}},
    {"UBER", {55, 55, 26, 29, 32, 48, 46, 50, 43, 49, 54}},
    {"MRNA", {150, 150, 68, 95, 117, 196, 235, 235, 171, 136, 108}},
    {"COST", {520, 551, 434, 434, 450, 558, 568, 559, 579, 634, 634}},
    {"KO", {60, 63, 47, 47, 49, 62, 64, 62, 64, 71, 71}},
    {"TSM", {120, 134, 80, 74, 74, 93, 91, 116, 93, 90, 64}},
    {"INTC", {55, 61, 36, 33, 33, 43, 43, 36, 49, 58, 78}},
    {"UAL", {40, 44, 22, 22, 24, 35, 38, 38, 33, 30, 35}}, // 3
    {"DAL", {45, 50, 26, 26, 28, 41, 43, 43, 37, 34, 40}} // 3
};

void Stage::startStage() {
    int playerRanking;
    for(Round r: rounds) {
        // 發技能給玩家
        switch (this->currentRound)
        {
        case 2:
        case 4:
        case 6:
        case 8:
            this->characters[0]->obtainSkill(randomInt(Foresight::getId(), Gamble::getId()));
            break;
        }
        

        // 重置角色操作次數
        for(Character* cha: this->characters)
            cha->resetActionCnt();

        // 事件發生->機器人先進行操作->玩家進行操作->回合結束->歷史價格更新->事件影響股價
        r.startRound(*this);

        // 更新歷史價格
        for(auto& stock: stocks)
        {
            stock.second->addToPriceHistory(stock.second->getCurrentPrice());
        }

        // 事件影響股價
        r.events[0]->affectStockPrice(stocks);
        r.events[1]->affectStockPrice(stocks);
        r.events[2]->affectStockPrice(stocks);

        // 增加玩家持股的回合數，清除本回合操作紀錄
        for(Character* cha: this->characters){
            for(auto& a: cha->assets)
                ++a.second.roundCnt;
            cha->clearActionLog();
        }

        // 依總資產排序角色，得到結果
        vector<Character*> sortedCharas(this->characters.begin(), this->characters.end());
        sort(sortedCharas.begin(), sortedCharas.end(), [](Character* a, Character* b){
            return a->getTotalAsset() > b->getTotalAsset();
        });

        if (currentRound == 10) {
            auto it = find(sortedCharas.begin(), sortedCharas.end(), this->characters[0]);
            playerRanking = distance(sortedCharas.begin(), it) + 1;
        }

        cout << "當前排行：\n";
        for(int i = 0; i < sortedCharas.size(); ++i){
            cout << i + 1 << ": " << sortedCharas[i]->getName() << "  總資產：" << sortedCharas[i]->getTotalAsset() << "\n";
        }

        if(currentRound == 10)
            cout << "按enter查看最終結果！\n";
        else
            cout << "按enter進入下回合\n";
        
        cin.get();
        cin.get();

        // 更新回合數
        ++currentRound;
    }

    // 輸出最終排名
    cout << "最終排名：" << playerRanking << "\n";
    if(playerRanking <= 3){
        cout << "恭喜獲勝！\n";
    } else {
        cout << "未能進入前三名，歡迎再次挑戰！\n";
    }
    cin.get();
// 印股價測試
// for(auto& p: this->stocks){
//     p.second->printHistory();
// }
}

void Round::startRound(Stage& stage) {
    cout << "當前回合數：" << stage.getCurRound() << "，";
    for(auto c = stage.characters.rbegin(); c != stage.characters.rend(); ++c) {
        (*c)->takeAction(stage, *this);
    }
}