#include "hive.h"

Hive::Hive() {
    this->messages = new UDPContainer();
    this->activity_log = new ActivityLog();
    this->pop_history = new std::vector<PopulationHistory*>();
    this->population = 10000;
    original_population = 10000;
}

Hive::Hive(int hive_id,int population){
    this->messages = new UDPContainer();
    this->activity_log = new ActivityLog();
    this->pop_history = new std::vector<PopulationHistory*>();
    this->hive_id = hive_id;
    this->population = population;
    this->original_population = population;
}

/**
 * @brief Hive::getPop
 * @return current population of hive
 */
int Hive::getPop(){
    return this->population;
}

/**
 * @brief Hive::get_original_pop
 * @return original population of hive
 */
int Hive::get_original_pop(){
    return this->original_population;
}

/**
 * @brief Hive::setPop sets current population
 * @param population
 */
void Hive::setPop(int population){
    this->population = population;
}

/**
 * @brief Hive::set_run_id sets run id of hive
 * @param run_id
 */
void Hive::set_run_id(int run_id){
    this->run_id = run_id;
}

/**
 * @brief Hive::setId sets hive id
 * @param hive_id
 */
void Hive::setId(int hive_id){
    this->hive_id = hive_id;
}

/**
 * @brief Hive::get_id
 * @return hive id
 */
int Hive::get_id(){
    return this->hive_id;
}

/**
 * @brief Hive::add_udp adds an UDP message to hive's list
 * @param udp
 */
void Hive::add_udp(UDP udp){
    this->messages->addMessage(udp);
}

/**
 * @brief Hive::id_as_string
 * @return hive id as a string
 */
std::string Hive::id_as_string(){
    std::string temp = "HC";
    char id[10];
    //sprintf_s(id, "%05d",this->hive_id);
    temp += id;
    return temp;
}

/**
 * @brief Hive::set_messages sets UDP message list of hive
 * @param udps
 */
void Hive::set_messages(UDPContainer *udps){
    delete messages;
    this->messages = udps;
}

/**
 * @brief Hive::save_to_file saves UDP messages of hive to a file
 */
void Hive::save_to_file(){
    std::string file_name = "../../DBee/dbee_run" + std::to_string(this->run_id);
    file_name += "_hive" + std::to_string(this->hive_id) + ".txt";
    this->messages->writeFile(file_name);
}

/**
 * @brief Hive::read_from_file reads UDP messages from a file
 */
void Hive::read_from_file(){
    std::string file_name = "../../DBee/dbee_run" + std::to_string(this->run_id);
    file_name += "_hive" + std::to_string(this->hive_id) + ".txt";
    this->messages = new UDPContainer(file_name);

    this->update_log();
    this->update_history();
}

/**
 * @brief Hive::print_pop_history prints out population history
 * @brief Population vs time
 */
void Hive::print_pop_history(){
    std::cout << "Initial pop: " << this->population << std::endl;
    for(unsigned i=0; i<this->pop_history->size(); i++){
        std::cout << "At time: " << this->pop_history->at(i) ->time->toString();
        std::cout << " Population: " << this->pop_history->at(i)->population;
        std::cout << std::endl;
    }
}

/**
 * @brief Hive::add_event adds a population history struct
 * @param new_event
 */
void Hive::add_event(PopulationHistory* new_event){
    this->pop_history->push_back(new_event);
}

/**
 * @brief Hive::update_log finds activity (entrance/exit) from UDP messages
 */
void Hive::update_log(){
    this->activity_log = this->messages->findActivity(100);
    delete this->messages;
}

/**
 * @brief Hive::update_history updates population history from activity log
 */
void Hive::update_history(){
    std::vector<Act>* log = this->activity_log->get_log();
    for(unsigned i=0; i<log->size(); i++){
        if(log->at(i).entered == 1){
            this->population++;
        } else{
            this->population--;
        }
        PopulationHistory* event = new PopulationHistory(log->at(i).t, this->population);
        this->add_event(event);
    }
    delete this->activity_log;
}

void Hive::print(){
//    std::cout << "Hive " << this->get_id() << std::endl;
//    this->messages->print();
//    this->activity_log->print();
}
