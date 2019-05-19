#ifndef RUNHISTORY_H
#define RUNHISTORY_H

#include <iostream>
#include <string>
#include "../../DBee/dbtool.h"
#include "../../DBee/dbtable.h"
#include "../../DBee/dbtablerun.h"
#include "run.h"

class DBTableRun;
class RunHistory
{
public:
    RunHistory();
    void add_prev_run(Run* run);
    void add_new_run(Run* run);
    void print();
    Run* get_run(unsigned index);
    int get_nb_runs(){return run_list->size();}
    void load_run_history();
    void save_run(Run* run);
private:
    std::vector<Run*> *run_list;
    void set_up();
    DBTool* dbTool;
    DBTableRun* table_run;
};

#endif // RUNHISTORY_H
