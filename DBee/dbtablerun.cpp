#include "dbtablerun.h"

//extern RunHistory* temp = new RunHistory();
DBTableRun::DBTableRun()
{
//    run_history = new RunHistory();
}

DBTableRun::DBTableRun(DBTool     *db,
                       std::string name   ) :
    DBTable (db, name)
{
//    run_history = new RunHistory();

    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

DBTableRun::~DBTableRun() {

}

void DBTableRun::set_run_history(RunHistory *run_history){
    this->run_history = run_history;
}

void DBTableRun::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}

void DBTableRun::store_create_sql() {

    //std::cerr << "calling store_create_sql from DBTableEx\n";

    sql_create =  "CREATE TABLE ";
    sql_create += table_name;
    sql_create += " ( ";
    sql_create += "  [Run ID] INT PRIMARY KEY, ";
    sql_create += " [Hive Number] INT NOT NULL,";
    sql_create += " Location TEXT NOT NULL,";
    sql_create += " [Est Total Pop] INT NOT NULL";
    sql_create += " );";

}

bool DBTableRun::add_row(int         run_id,
                         int hive_number,
                         std::string location,
                         int population) {
    int   retCode = 0;
    char *zErrMsg = 0;

    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " ( [Run ID], [Hive Number], Location, [Est Total Pop]) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", run_id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", hive_number);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += std::string(location);
    sql_add_row += "\",";

    sprintf (tempval, "%d", population);
    sql_add_row += tempval;
    sql_add_row += "); ";

//    std::cout << sql_add_row << std::endl;

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           dbrun_add_row,
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

bool DBTableRun::select_all() {

    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           dbrun_select_all,
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


int dbrun_add_row(void  *data,
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

    DBTableRun *obj = (DBTableRun *) data;

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

int dbrun_select_all(void  *data,
                     int    argc,
                     char **argv,
                     char **azColName)
{
//    std::cerr << "cb_select_all being called\n";

    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;

    DBTableRun *obj = (DBTableRun *) data;
//    obj->run_history
//    std::cout << "------------------------------\n";
//    std::cout << obj->get_name()
              //<< std::endl;
    int run_id = atoi(argv[0]);
    int num_hives = atoi(argv[1]);
    std::string location = std::string(argv[2]);
//    std::cout << std::endl << argv[0] << " " << argv[1] <<" " << argv[2] << std::endl;
    int population = atoi(argv[3]);
    Run* new_run = new Run(run_id,num_hives, location, population);

    if(obj->run_history != nullptr){
        obj->run_history->add_prev_run(new_run);
    }

    //for(i = 0; i < argc; i++){
    //    std::cout << azColName[i]
    //                 << " = "
    //                 <<  (argv[i] ? std::string(argv[i]) : "NULL")
    //                  << std::endl;
    //}

    return 0;
}
