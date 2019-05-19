#include "configuration.h"

/* constructor for Configuration */
Configuration::Configuration()
{

}

Configuration::Configuration(int num_hives, int avg_hive_size,std::string location){
    this->number_hives = num_hives;
    this->avg_hive_size = avg_hive_size;
    this->location = location;
    this->swarm_mode = false;
    this->constant_pop = true;
}

/**
 * @brief Configuration::set_swarm_mode sets if swarm mode is on
 * @param swarm
 */
void Configuration::set_swarm_mode(bool swarm){
    this->swarm_mode = swarm;
}

/**
 * @brief Configuration::set_constant_pop sets if population is not varied
 * @param value
 */
void Configuration::set_constant_pop(bool value){
    this->constant_pop = value;
}

/**
 * @brief Configuration::setNumHives sets number of hives
 * @param n
 */
void Configuration::setNumHives(int n) {
    number_hives = n;
}

/**
 * @brief Configuration::get_avg_size gets average hive population (specified in GUI)
 * @return
 */
int Configuration::get_avg_size(){
    return this->avg_hive_size;
}

/**
 * @brief Configuration::getNumHives
 * @return number of hives
 */
int Configuration::getNumHives() {
    return number_hives;
}

/**
 * @brief Configuration::get_location
 * @return location of simulation
 */
std::string Configuration::get_location(){
    return this->location;
}

/**
 * @brief Configuration::get_constant_pop
 * @return if constant population is wanted
 */
bool Configuration::get_constant_pop(){
    return this->constant_pop;
}

/**
 * @brief Configuration::get_swarm_mode
 * @return if swarm mode is wanted
 */
bool Configuration::get_swarm_mode(){
    return this->swarm_mode;
}
