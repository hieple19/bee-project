#include "runhistory.h"

RunHistory::RunHistory()
{
    run_list = new std::vector<Run*>();
    dbTool = new DBTool("../../DBee/dbee_run.sqlite");
    table_run = new DBTableRun(dbTool,"TableRun");
    table_run->set_run_history(this);
    table_run->select_all();
}

/**
 * @brief RunHistory::add_prev_run adds a previous run
 * @param run
 */
void RunHistory::add_prev_run(Run* run){
    this->run_list->push_back(run);
    //run->print();

}

/**
 * @brief RunHistory::add_new_run adds a new run
 * @param run
 */
void RunHistory::add_new_run(Run *run){
    this->run_list->push_back(run);
}

/**
 * @brief RunHistory::save_run saves a run to database
 * @param run
 */
void RunHistory::save_run(Run* run){
    table_run->add_row(run->get_run_id(),run->get_num_hives(),run->get_location(), run->get_total_population());

}

/**
 * @brief RunHistory::load_run_history calls each run to load
 * their info
 */
void RunHistory::load_run_history(){
    for(unsigned i =0; i<run_list->size(); i++){
        run_list->at(i)->load_run_info();
    }
}

/**
 * @brief RunHistory::get_run gets a run based on index
 * @param index
 * @return run at index
 */
Run* RunHistory::get_run(unsigned index){
    return this->run_list->at(index);
}

void RunHistory::print(){
    for(unsigned i = 0; i<run_list->size(); i++){
        run_list->at(i)->print();
    }
}
