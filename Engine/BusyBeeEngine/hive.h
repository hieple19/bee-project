#ifndef HIVE_H
#define HIVE_H

#include <iostream>
#include <string>
#include "../../Tools/mstime.h"
#include "../../Tools/udpcontainer.h"
#include "../../Tools/activity.h"

// Struct to keep track of population vs time
struct PopulationHistory
{
        PopulationHistory(MStime* time_, int pop_)
            : time(time_), population(pop_) {}
        MStime*  time;
        int     population;
};


class Hive {
public:
    Hive();
    Hive(int hive_id,int population);
    UDPContainer* get_udp_messages();

    void update_log();
    void add_udp(UDP udp);
    void set_run_id(int run_id);
    int get_id();
    void setId(int hive_id);
    std::string id_as_string();
    int getPop();
    int get_original_pop();
    void setPop(int population);

    void print();
    std::vector<PopulationHistory*>* get_pop_history(){return pop_history;};

    void set_messages(UDPContainer* udps);
    void add_event(PopulationHistory* new_event);
    void update_history();
    void print_pop_history();
    void save_to_file();
    void read_from_file();
private:
    int hive_id;
    int run_id;

    std::string owner;
    std::string city;
    std::string ZIP;
    int original_population;
    int population;
    std::string status;
    MStime last_updated;
    UDPContainer* messages;
    ActivityLog* activity_log;

   std::vector<PopulationHistory*>* pop_history;
};



#endif // HIVE_H
