#ifndef DBTABLEUDP_H
#define DBTABLEUDP_H


#include <iostream>
#include <string>
#include "sqlite3.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "dbtool.h"
#include "dbtable.h"

class DBTableUDP : public DBTable {

protected:

    std::string sql_select_all;

public:

    DBTableUDP();
    DBTableUDP(DBTool     *db,
              std::string name);

    ~DBTableUDP();

    // An overloaded method to generate a new
    // create command for your child class.
    void store_create_sql();

    // An overloaded method to generate a new
    // insert command for your child class.
    virtual void store_add_row_sql();

    bool add_row(std::string hive_id, std::string udp_mes);

    bool select_all();
};


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int dbudp_add_row(void  *data,
               int    argc,
               char **argv,
               char **azColName);


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int dbudp_select_all(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

#endif // DBTABLEUDP_H
