#ifndef ACTIVITYGEN_H
#define ACTIVITYGEN_H

#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>

#include "udp.h"
#include "udpcontainer.h"
using namespace std;
class ActivityGen
{
public:
    ActivityGen(string file_name, int seed);
    vector<int> generate();
    void print_times();
private:
    int seed;
    int num_of_boards;
    int num_of_gates;

    void config_gen(int board_num, int gate_num);
    void generate_data(int duration);
    string file_name;
    vector<int> lambdas;
    vector<double> times;
};

#endif // ACTIVITYGEN_H
