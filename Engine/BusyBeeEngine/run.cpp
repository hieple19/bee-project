#include "run.h"

Run::Run()
{
    this->hive_list = new std::vector<Hive*>();
    this->num_hives = 0;
}

Run::Run(int run_id,int num_hives, std::string location, int avg_population){
    this->run_id = run_id;
    this->num_hives = num_hives;
    this->location = location;
    this->avg_population = avg_population;
    this->hive_list = new std::vector<Hive*>();
}

Run::Run(int run_id, Configuration* config, ExternalConditions* ec){
    this->hive_list = new std::vector<Hive*>();
    this->run_id = run_id;
    this->config = config;
    this->ec = ec;
    this->num_hives = this->config->getNumHives();
    this->avg_population = this->config->get_avg_size();
    this->location = this->config->get_location();
}

/**
 * @brief Run::get_run_id
 * @return Run ID
 */
int Run::get_run_id(){
    return this->run_id;
}

/**
 * @brief Run::get_total_population
 * @return sum of population of all hives
 */
int Run::get_total_population(){
    int sum = 0;
    for(unsigned i=0; i<this->hive_list->size(); i++){
        sum+= this->hive_list->at(i)->getPop();
    }
    return sum;
}

/**
 * @brief Run::get_hives_list
 * @return list of hives in run
 */
std::vector<Hive*>* Run::get_hives_list(){
    return this->hive_list;
}

/**
 * @brief Run::set_population sets average population for simulation run
 * @param pop
 */
void Run::set_population(int pop){
    this->avg_population = pop;
}

/**
 * @brief Run::get_location
 * @return location of simulation run
 */
std::string Run::get_location() {return this->location;}

/**
 * @brief Run::set_location sets location of run
 * @param location
 */
void Run::set_location(std::string location){
    this->location = location;
}

/**
 * @brief Run::get_num_hives
 * @return number of hives
 */
int Run::get_num_hives() {return this->num_hives;}

/**
 * @brief Run::get_avg_population
 * @return average population of each hive
 */
int Run::get_avg_population() {return this->avg_population;}

/**
 * @brief Run::add_hive adds a hive to list of hives and update hive count
 * @param hive
 */
void Run::add_hive(Hive* hive){
    this->num_hives++;
    this->hive_list->push_back(hive);
}
/**
 * @brief Run::initialize_hives initializes hive with a population
 * determined by conditions specified in the GUI. Add hive to list
 * of hives in Run object. Save population data of hives to files
 */
void Run::initialize_hives(){
    std::string file_name = "../../DBee/dbee_run" + std::to_string(run_id) + "_hive_population.txt";    std::ofstream out(file_name);
    int seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine dre;
    dre.seed(seed);
    std::uniform_real_distribution<double> distribution(-0.4,0.4);
    for (int i=0; i<this->num_hives; i++) {

        // Vary population based on GUI condition
        double random_percent = 0;
        if(!config->get_constant_pop()){
            random_percent = distribution(dre);
        }

        int random_population = (1+random_percent)*avg_population;
        out << random_population << std::endl;

        Hive* new_hive = new Hive(i+1, random_population);
        new_hive->set_run_id(this->run_id);
        this->hive_list->push_back(new_hive);
    }

    out.close(); // Save population data to a file
}

/**
 * @brief Run::save_run_info calls each hive in run to save data
 */
void Run::save_run_info(){
    for(int i =0; i<this->num_hives; i++){
        this->hive_list->at(i)->save_to_file();
    }
}

/**
 * @brief Run::load_run_info loads population data of each hive
 * and calls each hive to load UDP messages
 */
void Run::load_run_info(){
    std::string input_file = "../../DBee/dbee_run" + std::to_string(run_id) + "_hive_population.txt";
    std::ifstream in(input_file);
    std::string line;

    if(!in.is_open()){
        std::cout << "Error open population data \n";
    }
    for(int i =0; i<this->num_hives; i++){
        getline(in,line);
        int population = std::stoi(line);

        this->hive_list->push_back(new Hive(i+1, population));
        this->hive_list->at(i)->set_run_id(this->run_id);
        this->hive_list->at(i)->read_from_file();
    }
}


void Run::print(){
    std::cout << std::endl << std::endl;
    std::cout << "Run ID: " << this->run_id << std::endl;
    std::cout << "Num. of hives: " << num_hives << " " << location << " Total Pop: " << this->get_total_population() << std::endl;
    for(unsigned i=0; i<this->hive_list->size(); i++){
        std::cout << std::endl;
        std::cout << "Hive " << (i+1) << std::endl;
        //        this->hive_list->at(i)->print();
        this->hive_list->at(i)->print_pop_history();
    }
}

