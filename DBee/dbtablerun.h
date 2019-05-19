#ifndef DBTABLERUN_H
#define DBTABLERUN_H

#include <iostream>
#include <string>
#include "sqlite3.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "dbtool.h"
#include "dbtable.h"
#include "../Tools/mstime.h"
#include "../Engine/BusyBeeEngine/runhistory.h"

class RunHistory;
class DBTableRun : public DBTable {

protected:

    std::string sql_select_all;

public:

    DBTableRun();
    DBTableRun(DBTool     *db,
              std::string name);

    ~DBTableRun();

    RunHistory* run_history;
    void set_run_history(RunHistory* run_history);
    // An overloaded method to generate a new
    // create command for your child class.
    void store_create_sql();

    // An overloaded method to generate a new
    // insert command for your child class.
    virtual void store_add_row_sql();

    bool add_row(int run_id,
                 int hive_number,
                 std::string location,
                 int population);

    bool select_all();
};


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int dbrun_add_row(void  *data,
               int    argc,
               char **argv,
               char **azColName);


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int dbrun_select_all(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

#endif // DBTABLERUN_H
