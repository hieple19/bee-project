#include "busybeeengine.h"

/* constructor for BusyBeeEngine */
BusyBeeEngine::BusyBeeEngine(){
    this->run_history = new RunHistory();
}
BusyBeeEngine::BusyBeeEngine(Configuration* configuration)
{
    this->config = configuration;
    this->run_history = new RunHistory();
    output_controller = new OutputController(configuration); // initialize OutputController with argument configuration
}

BusyBeeEngine::BusyBeeEngine(Configuration* configuration, ExternalConditions* ec){
    this->config = configuration;
    this->conditions = ec;
}

/**
 * @brief BusyBeeEngine::make_new_run initializes a new run and add run
 * to run history stored in engine
 */
void BusyBeeEngine::make_new_run(){
    this->current_run = new Run(this->run_history->get_nb_runs()+1, this->config, this->conditions);
    this->current_run->initialize_hives();
    this->run_history->add_new_run(this->current_run);
}

/**
 * @brief BusyBeeEngine::set_run sets current run to a specific run
 * @param run
 */
void BusyBeeEngine::set_run(Run* run){
    this->current_run = run;
}

/**
 * @brief BusyBeeEngine::add_new_run adds a new run and set to be current run
 * @param run
 */
void BusyBeeEngine::add_new_run(Run* run){
    this->current_run = run;
    this->run_history->add_new_run(run);
}

/**
 * @brief BusyBeeEngine::set_conditions sets external condition
 * @param ec
 */
void BusyBeeEngine::set_conditions(ExternalConditions* ec){
    this->conditions = ec;
}

/**
 * @brief BusyBeeEngine::set_config
 * @param config
 */
void BusyBeeEngine::set_config(Configuration *config){
    this->config = config;
}

/**
 * @brief BusyBeeEngine::simulate starts a simulation given the parameters
 */
void BusyBeeEngine::simulate(){
    Simulation s = Simulation(config, conditions, current_run);
    s.simulate_all_hives();
}

/**
 * @brief BusyBeeEngine::save_run saves current run info
 */
void BusyBeeEngine::save_run(){
    //    this->current_run->save_run_info();
    this->run_history->save_run(this->current_run);
}

/**
 * @brief BusyBeeEngine::load_run_history loads previous run history
 */
void BusyBeeEngine::load_run_history(){
    this->run_history->load_run_history();
}

/**
 * @brief BusyBeeEngine::load_run loads data of current run
 */
void BusyBeeEngine::load_run(){
    this->current_run->load_run_info();
}

void BusyBeeEngine::print(){
    this->run_history->print();
}
