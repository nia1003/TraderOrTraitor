#include <iostream>
#include <vector>
#include "Event.h"
#include "stock.h"
using namespace std;

int main()
{
    // 模擬創建一個 Stock 物件
    Stock Apple(101, "Apple", "Technology", 120.5, "A leading tech company.", 0.8);
    
    // 模擬一些歷史價格數據
    Apple.addToPriceHistory(110.0); // 添加方法需實作
    Apple.addToPriceHistory(115.0);
    Apple.addToPriceHistory(118.0);

    // 輸出股票資訊
    Apple.printStockInfo();

    /*設定個股和事件數值

    */

return 0;

}