// contains definition of Act struct, which has information regarding entrances/exits, hive, and time
// ActivityLog is a container for Acts, and can print its contents for debugging

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <vector>
#include "mstime.h"

struct Act {
    int hiveID; // ID of the hive this occured at
    bool entered; // true if this activity is an entrance, false for exit
    MStime* t; // time this actity occured at
};

// wrapper for vector containing a list of activities (entrances and exits)
class ActivityLog{
public:
    ActivityLog();
    void addAct(int, bool, MStime*);
    std::vector<Act>* get_log(){return &log;}
    void print();
private:
    std::vector<Act> log;
};

#endif // ACTIVITY_H
