#ifndef HIVE_H
#define HIVE_H

#include <iostream>
#include <string>
#include "../../Tools/mstime.h"

class Hive {
public:
    Hive();
    int getSize();
    int getNBoards();
    void setSize(int s);
    void setNBoards(int boards);
private:
    int size; // size of hive
    std::string hive_id;
    std::string farm_id;
    std::string owner;
    std::string city;
    std::string ZIP;
    int population;
    std::string status;
    MStime last_updated;
    int nBoards; // number of boards
};

#endif // HIVE_H
