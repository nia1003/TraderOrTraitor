#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <unordered_map>

class Event {
public:
    Event(const std::string& description, const std::unordered_map<std::string, double>& affectedStocks);
    void applyImpact(std::vector<class Stock>& stocks) const;

    std::string getDescription() const;

private:
    std::string description;
    std::unordered_map<std::string, double> affectedStocks; // 儲存每個股票及其影響的百分比
};

#endif
