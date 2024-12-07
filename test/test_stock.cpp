#include <iostream>
#include <vector>
#include <windows.h>
#include "../Event.h"
#include "../Stock.h"
using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8
    // 初始化股票列表
    unordered_map<string, Stock> stockMap = 
    {
        {"AAPL", Stock("AAPL", "Apple Inc.", "Technology", 150, "疫情期間持續推出創新產品，並加速研發自家晶片，硬體需求保持強勁。然而，疫情後需關注一般消費者的購買力是否能夠支撐其營收增長。", 0.8)},
        {"MSFT", Stock("MSFT", "Microsoft", "Technology", 280, "受益於遠端辦公需求以及 Azure 雲端業務的增長，近期業績表現穩定，未來發展值得關注。", 0.8)},
        {"UBER", Stock("UBER", "Uber", "Technology", 55, "疫情期間載客需求顯著減少，業務面臨挑戰，但未來需求回升的可能性仍需觀察。", 1.3)},
        {"MRNA", Stock("MRNA", "Moderna", "Biotech", 150, "疫苗研發取得成功，疫情後期業務增長顯著，但長期表現仍存在不確定性，須注意疫苗是否能被各國認可。", 1.7)},
        {"COST", Stock("COST", "Costco", "Consumer Staples", 520, "疫情期間囤貨需求激增，但未來趨勢仍需觀察", 0.6)},
        {"KO", Stock("KO", "Coca-Cola", "Consumer Staples", 60, "飲料需求保持穩定，但長期增長可能取決於消費者習慣的變化", 0.7)},
        {"TSM", Stock("TSM", "Taiwan Semiconductor Manufacturing", "Semiconductor", 120, "作為晶圓代工龍頭，持續受益於先進晶片需求，需要特別注意與英特爾的競爭壓力", 1.0)},
        {"INTC", Stock("INTC", "Intel", "Semiconductor", 55, "老牌半導體公司，近期擴張晶圓代工業務，與台積電處於劇烈競爭的狀態", 1.0)},
        {"UAL", Stock("UAL", "United Airlines", "Airlines", 40, "旅遊需求驟降，業績遭受重創，但疫苗問世可能帶來復甦希望", 1.2)},
        {"DAL", Stock("DAL", "Delta Air Lines", "Airlines", 45, "作為航空業龍頭之一，疫苗普及推動旅遊需求回升，但挑戰依然存在", 1.2)}
    };

    vector<Stock> stockVector = 
    {
        {Stock("AAPL", "Apple Inc.", "Technology", 150, "疫情期間持續推出創新產品，並加速研發自家晶片，硬體需求保持強勁。然而，疫情後需關注一般消費者的購買力是否能夠支撐其營收增長。", 0.8)},
        {Stock("MSFT", "Microsoft", "Technology", 280, "受益於遠端辦公需求以及 Azure 雲端業務的增長，近期業績表現穩定，未來發展值得關注。", 0.8)},
        {Stock("UBER", "Uber", "Technology", 55, "疫情期間載客需求顯著減少，業務面臨挑戰，但未來需求回升的可能性仍需觀察。", 1.3)},
        {Stock("MRNA", "Moderna", "Biotech", 150, "疫苗研發取得成功，疫情後期業務增長顯著，但長期表現仍存在不確定性，須注意疫苗是否能被各國認可。", 1.7)},
        {Stock("COST", "Costco", "Consumer Staples", 520, "疫情期間囤貨需求激增，但未來趨勢仍需觀察", 0.6)},
        {Stock("KO", "Coca-Cola", "Consumer Staples", 60, "飲料需求保持穩定，但長期增長可能取決於消費者習慣的變化", 0.7)},
        {Stock("TSM", "Taiwan Semiconductor Manufacturing", "Semiconductor", 120, "作為晶圓代工龍頭，持續受益於先進晶片需求，需要特別注意與英特爾的競爭壓力", 1.0)},
        {Stock("INTC", "Intel", "Semiconductor", 55, "老牌半導體公司，近期擴張晶圓代工業務，與台積電處於劇烈競爭的狀態", 1.0)},
        {Stock("UAL", "United Airlines", "Airlines", 40, "旅遊需求驟降，業績遭受重創，但疫苗問世可能帶來復甦希望", 1.2)},
        {Stock("DAL", "Delta Air Lines", "Airlines", 45, "作為航空業龍頭之一，疫苗普及推動旅遊需求回升，但挑戰依然存在", 1.2)}      
    };

    // 連同初始價格，共有11個歷史價格
    unordered_map<string, array<int, 11>> price_per_round = 
    {
        {"AAPL", {150, 159, 114, 127, 133, 184, 174, 177, 177, 206, 206}},
        {"MSFT", {280, 290, 209, 233, 241, 308, 286, 280, 269, 314, 314}},
        {"UBER", {55, 55, 26, 29, 32, 48, 46, 50, 43, 49, 54}}, 
        {"MRNA", {150, 150, 129, 181, 224, 376, 452, 452, 329, 261, 207}}, 
        {"COST", {520, 551, 434, 434, 450, 558, 568, 559, 579, 634, 634}},
        {"KO", {60, 63, 47, 47, 49, 62, 64, 62, 64, 71, 71}},
        {"TSM", {120, 134, 80, 74, 74, 93, 91, 116, 93, 90, 64}},
        {"INTC", {55, 61, 36, 33, 33, 43, 43, 36, 49, 58, 78}},
        {"UAL", {40, 44, 22, 24, 26, 38, 41, 41, 36, 33, 39}}, 
        {"DAL", {45, 50, 26, 28, 30, 44, 46, 46, 40, 37, 44}} 
    };  


return 0;

}