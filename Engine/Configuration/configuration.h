#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../BusyBeeEngine/hive.h"

#include <iostream>
using namespace std;

class Hive;

class Configuration {
public:
    Configuration();
    Configuration(int num_hives, int avg_hive_size, std::string location);
    void setNumHives(int n);
    int getNumHives();
    int get_avg_size();
    std::string get_location();
    bool get_constant_pop();
    bool get_swarm_mode();
    void set_constant_pop(bool value);
    void set_swarm_mode(bool swarm);
private:
    int number_hives;
    int avg_hive_size;
    int number_boards_per_hive;
    std::string location;
    bool constant_pop;
    bool swarm_mode;
};

#endif // CONFIGURATION_H
