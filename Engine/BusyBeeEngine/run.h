#ifndef RUN_H
#define RUN_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <cmath>


#include <vector>

#include "hive.h"
#include "../Configuration/configuration.h"
#include "../ExternalConditions/ExternalConditions.h"

class Run
{
public:
    Run();
    Run(int run_id,int num_hives, std::string location, int population);
    Run(int run_id, Configuration* config, ExternalConditions* ec);

    void print();
    int get_num_hives();
    std::string get_location();
    int get_avg_population();
    void set_population(int pop);
    void set_location(std::string location);
    std::vector<Hive*> *get_hives_list();
    void add_hive(Hive* hive);
    void initialize_hives();
    int get_run_id();
    int get_total_population();
    void save_run_info();
    void load_run_info();
private:
    int run_id;
    std::string location;
    int avg_population;
    int num_hives;
    std::vector<Hive*>* hive_list;
    Configuration* config;
    ExternalConditions* ec;

};

#endif // RUN_H
