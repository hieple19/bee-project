#include <iostream>
#include <ctime>
#include "../Tools/mstime.h"
#include "dbtable.h"
#include "dbtablerun.h"
#include "dbtableudp.h"
#include "dbtablestatus.h"
#include "dbtablehive.h"
#include "dbtool.h"

using namespace std;

int main()
{
    DBTool* dbTool = new DBTool("dbee_run.sqlite");
    DBTableRun *db_run = new DBTableRun(dbTool, "TableRun");
//    db_run->add_row(1,3,"Easton, PA", 10000);
//    db_run->add_row(2,2, "Palo Alto, CA", 30000);
//    db_run->add_row(3,2, "Trenton, NJ",20000);
    db_run->select_all();


  DBTableStatus *db_status = new DBTableStatus(dbTool, "TableStatus");

    time_t now = time(NULL);
    struct tm* tm = localtime(&now);
    MStime* time_now = new MStime(tm,0);
 //   db_status->add_row("HC001","004","RPA",*time_now,"Easton","PA","18042",2000,"Healthy");
    db_status->select_all();

    DBTableUDP *db_udp = new DBTableUDP(dbTool, "TableUDP");
//    db_udp->add_row("HC001","HC0002 - D18.12.19 T13.43.16.000 B0B1B16B0B0B0B0B0B0B0");
    db_udp->select_all();

    DBTableHive *db_hive = new DBTableHive(dbTool, "TableHive");
//    db_hive->add_row(*time_now, "In");
    db_hive->select_all();
    return 0;
}
