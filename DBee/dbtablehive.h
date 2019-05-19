#ifndef DBTABLEHIVE_H
#define DBTABLEHIVE_H
#include <iostream>
#include <string>
#include "sqlite3.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "dbtool.h"
#include "dbtable.h"
#include "dbtablestatus.h"
#include "../Tools/mstime.h"
#include <time.h>
#include <ctime>

class DBTableHive: public DBTable
{
protected:

    std::string sql_select_all;

public:

    DBTableHive();
    DBTableHive(DBTool     *db,
              std::string name);

    ~DBTableHive();
    void store_create_sql();

    // An overloaded method to generate a new
    // insert command for your child class.
    virtual void store_add_row_sql();

    bool add_row(MStime event_time, std::string movement);

    bool select_all();
};

int dbhive_add_row(void  *data,
                     int    argc,
                     char **argv,
                     char **azColName);

int dbhive_select_all(void  *data,
                        int    argc,
                        char **argv,
                        char **azColName);
#endif // DBTABLEHIVE_H
