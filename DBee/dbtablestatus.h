#ifndef DBTABLESTATUS_H
#define DBTABLESTATUS_H

#include <iostream>
#include <string>
#include "sqlite3.h"
#include "../Tools/mstime.h"
#include <time.h>
#include <ctime>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>


#include "dbtool.h"
#include "dbtable.h"

class DBTableStatus : public DBTable
{
protected:

    std::string sql_select_all;

public:
    DBTableStatus();
    DBTableStatus(DBTool     *db,
                  std::string name);

    ~DBTableStatus();

    // An overloaded method to generate a new
    // create command for your child class.
    void store_create_sql();

    // An overloaded method to generate a new
    // insert command for your child class.
    virtual void store_add_row_sql();

    bool add_row(std::string hive_id,
                 std::string farm_id,
                 std::string owner,
                 MStime last_updated,
                 std::string city,
                 std::string state,
                 std::string zip,
                 int population,
                 std::string status);

    bool select_all();
};

int dbstatus_add_row(void  *data,
                     int    argc,
                     char **argv,
                     char **azColName);


int dbstatus_select_all(void  *data,
                        int    argc,
                        char **argv,
                        char **azColName);
#endif // DBTABLESTATUS_H
