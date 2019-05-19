#include <iostream>
#include "runhistory.h"
#include "busybeeengine.h"
#include "hive.h"
#include "../Configuration/configuration.h"
using namespace std;

int main()
{
    Configuration* c = new Configuration();
    BusyBeeEngine* engine = new BusyBeeEngine(c);
    engine->load_run_history();

     //Uncomment to start run
//    Run* new_run = new Run(1,2,"New York", 25000); // RunID, Num_hives, location, avg population
//    new_run->initialize_hives();
//    engine->add_new_run(new_run);
//    engine->simulate();
//    engine->print();
//    engine->save_run();

//    engine->load_run_history();
    engine->print();
    return 0;
}

