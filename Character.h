#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <Stock.h>
using namespace std;

class Character{
protected:
    // ��������
    short id;
    string identity; // �Ϊ����μƦr��ܨ���
    string name;
    string description;

    // �\�����
    int initBonus; // �i��]�p������¦�Ȧh��
    int currentMoney;
    vector<Stock> stocks;

public:
    int getCurrentMoney();
    string getName();
    // get identity
    string getDesciption();
    int getTotalAsset(); // currentMoney + �U(s.num * s.price) for s in stocks
};

#endif // CHARACTER_H
