#include "activity.h"
#include <iostream>
using namespace std;

ActivityLog::ActivityLog() {

}

// add an Act to the end of the activity log
void ActivityLog::addAct(int id, bool b, MStime* t){
    log.push_back(Act{id,b,t});
}

// print out the contents of this activity log for debugging
void ActivityLog::print(){
    std::cout << "Activity log: " << std::endl;
    unsigned long long size = log.size();

    for (unsigned long i = 0; i < size; i++){
        string s = "";
        if (log.at(i).entered) { s = "Entrance";}
        else { s = "Exit";}

        cout << s << " at hive " << log.at(i).hiveID << " on " << log.at(i).t->toString() << endl;
    }
}
