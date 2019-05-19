// class to generate simulated data using the contained external conditions and configuration

#ifndef SIMULATION_H
#define SIMULATION_H

#include "../ExternalConditions/ExternalConditions.h"
#include "../../Tools/udpcontainer.h"           // this includes udp.h and activity.h
#include "../Configuration/configuration.h"
#include "../BusyBeeEngine/hive.h"
#include "../BusyBeeEngine/run.h"

#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <string>

class Simulation {
public:
    Simulation();
    Simulation(Configuration* c, ExternalConditions* ec, Hive* hi); // constructor
    Simulation(Configuration* c, ExternalConditions* ec, Run* run);
    ~Simulation();
    UDPContainer* run();
    UDPContainer* runSwarm();
    void simulate_all_hives();

private:
    Run* current_run;
    Hive* current_hive; // hive for this simulation
    std::vector<Hive*>* hives_list;
    ExternalConditions* extCon; //  external conditions for this simulation
    Configuration* config; // configuration settings for this simulation
    long long seed;
    default_random_engine dre;
    bool swarm_mode;
};

#endif // SIMULATION_H
