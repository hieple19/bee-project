#ifndef BUSYBEEENGINE_H
#define BUSYBEEENGINE_H
#include "../Configuration/configuration.h"
#include "../OutputController/outputcontroller.h"
#include "../ExternalConditions/ExternalConditions.h"
#include "../Simulation/simulation.h"

#include "run.h"
#include "runhistory.h"

class Configuration;
class OutputController;
class BusyBeeEngine
{
public:
    BusyBeeEngine();
    BusyBeeEngine(Configuration* configuration);
    BusyBeeEngine(Configuration* configuration, ExternalConditions* ec);

    void simulate();
    void set_run(Run* run);
    void set_conditions(ExternalConditions* ec);
    void set_config(Configuration* config);
    void add_new_run(Run* run);
    void make_new_run();
    void save_run();
    void load_run();
    void print();
    void load_run_history();
    RunHistory* get_history(){return run_history;}

private:
    OutputController * output_controller;
    Configuration* config;
    ExternalConditions* conditions;
    Run* current_run;
    RunHistory* run_history;
};

#endif // BUSYBEEENGINE_H
