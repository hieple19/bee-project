#include "dbtablestatus.h"

DBTableStatus::DBTableStatus()
{

}

DBTableStatus::DBTableStatus(DBTool     *db,
                             std::string name   ) :
    DBTable (db, name)
{

    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

DBTableStatus::~DBTableStatus() {

}


void DBTableStatus::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}

void DBTableStatus::store_create_sql() {

    //std::cerr << "calling store_create_sql from DBTableEx\n";

    sql_create =  "CREATE TABLE ";
    sql_create += table_name;
    sql_create += " ( ";
    sql_create += "  [Hive ID] TEXT PRIMARY KEY NOT NULL, ";
    sql_create += "  [Farm ID] TEXT NOT NULL,";
    sql_create += "  Owner TEXT  NOT NULL, ";
    sql_create += "  [Last Updated] REAL  NOT NULL, ";
    sql_create += "  City TEXT NOT NULL,";
    sql_create += "  State TEXT NOT NULL,";
    sql_create += "  ZIP TEXT NOT NULL,";
    sql_create += "  Population INT NOT NULL,";
    sql_create += "  Status TEXT NOT NULL";
    sql_create += " );";
}


bool DBTableStatus::add_row(std::string hive_id,
                            std::string farm_id,
                            std::string owner,
                            MStime last_updated,
                            std::string city,
                            std::string state,
                            std::string zip,
                            int population,
                            std::string status){

    int   retCode = 0;
    char *zErrMsg = 0;

        char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " ([Hive ID], [Farm ID], Owner, [Last Updated], City, State, ZIP, Population, Status) ";
    sql_add_row += "VALUES (";

    sql_add_row += "\"";
    sql_add_row += std::string(hive_id);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(farm_id);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(owner);
    sql_add_row += "\", ";

    double time =  mktime(last_updated.getTmp());
    time += last_updated.getMS();
//    int ms = last_updated->ms;
//    int sec = last_updated->t->tm_sec;
//    int min = last_updated->t->tm_min;
//    int hour = last_updated->t->tm_hour;
//    int mday = last_updated->t->tm_mday;
//    int mon = last_updated->t->tm_mon;
//    int year = 1900 + last_updated->t->tm_year;

//    std::string date_string = std::to_string(year) + "-";
//    date_string += std::to_string(mon) + "-";
//    date_string += std::to_string(mday) + " ";
//    date_string += std::to_string(hour) + ":";
//    date_string += std::to_string(min) + ":";
//    date_string += std::to_string(sec) + ".";
//    date_string += std::to_string(ms);

//    sql_add_row += "\"";
    sprintf (tempval, "%.3f", time );
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += std::string(city);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(state);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(zip);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::to_string(population);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(status);
    sql_add_row += "\" );";
//    sql_add_row += ");";

    std::cout << sql_add_row << std::endl;

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           dbstatus_add_row,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}


bool DBTableStatus::select_all() {

    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           dbstatus_select_all,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

int dbstatus_add_row(void  *data,
                     int    argc,
                     char **argv,
                     char **azColName)
{
    std::cerr << "cb_add_row being called\n";

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBTableStatus *obj = (DBTableStatus *) data;

    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;

    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                     << " = "
                     <<  (argv[i] ? argv[i] : "NULL")
                      << std::endl;
    }

    return 0;
}


int dbstatus_select_all(void  *data,
                        int    argc,
                        char **argv,
                        char **azColName)
{
    std::cerr << "cb_select_all being called\n";

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBTableStatus *obj = (DBTableStatus *) data;

    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;

    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                     << " = "
                     <<  (argv[i] ? std::string(argv[i]) : "NULL")
                      << std::endl;
    }

    return 0;
}
