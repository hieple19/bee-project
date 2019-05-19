#include "simulation.h"

Simulation::Simulation(){
    seed = chrono::system_clock::now().time_since_epoch().count();
    dre = default_random_engine(seed);
    swarm_mode = false;
}

/* constructor takes in three arguments */
Simulation::Simulation(Configuration* c, ExternalConditions* ec, Hive* hi) {
    config = c;
    extCon = ec;
    current_hive = hi;
    current_run = nullptr;
    seed = chrono::system_clock::now().time_since_epoch().count();
    dre = default_random_engine(seed);
    swarm_mode = false;
}

Simulation::Simulation(Configuration* c, ExternalConditions* ec, Run* run){
    config = c;
    extCon = ec;
    current_run = run;
    hives_list = run->get_hives_list();
    seed = chrono::system_clock::now().time_since_epoch().count();
    dre = default_random_engine(seed);
    swarm_mode = c->get_swarm_mode();
}

// run simulations on each hive in the list
void Simulation::simulate_all_hives(){
    this->swarm_mode = this->config->get_swarm_mode();
    for(unsigned i = 0; i < hives_list->size(); i++){
        current_hive = hives_list->at(i);
        UDPContainer* udps;
        unsigned int num = dre();
        if (num % 20 == 0 || swarm_mode){
            udps = runSwarm();
        } else{
            udps = run();
        }

        current_hive->set_messages(udps);
//        std::cout << "Saving Hive UDP to file" << std::endl;
        current_hive->save_to_file();
        current_hive->update_log();
        current_hive->update_history();
    }
}

Simulation::~Simulation(){
    delete config;
    delete extCon;
}

// run the simulation
UDPContainer* Simulation::run(){
    UDPContainer* uc = new UDPContainer();

    // for now the time is just the current day month and year
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    MStime t = MStime(localtime(&now));
    t.getTmp()->tm_hour=0; t.getTmp()->tm_min=0; t.getTmp()->tm_sec=0; // set simulation to start at midnight

    // making factors that effect activity
    int pop = current_hive->getPop();
    double kconst = 0.03;               // constant conversion factor
    double ktemp;                       // temperature factor
    double kseason;                     // seasonal factor
    double kweather;                    // weather factor

    // finding kseason
    int s = extCon->getSeason();
    if (s == 1 || s == 2) {kseason = 0.5;}  // summer, autumn
    else if (s == 0) kseason = 1;           // spring
    else {kseason = 0.05;}                  // winter

    // finding kweather
    int w = extCon->getWeather();
    if (w == 0 || w == 3) {kweather = 0.05;}    // snow, rain
    else if (w == 1) kweather = 1;              // sunny
    else {kweather = 0.6;}                      // windy

    // finding ktemp
    ktemp = 0.8 + ((extCon->getTemp() - 20) / 100.0); // higher temp -> more activity

    poisson_distribution<unsigned int> pois(static_cast<unsigned int>(pop * kconst * kseason * kweather * ktemp)); // number of activities this time step determined by k and pop
    unsigned long dt = 600000; // change in time in milliseconds (10 minutes)

    // loops through 24 hours
    for (unsigned int i = 0; i < (24*60*60*1000/dt); i++) {
        unsigned int numAct = pois(dre); // find a random number of activities to occur this time step

        // loop through each activity
        for (unsigned int j = 0; j < numAct; j++){
            MStime t1 = t + ((dt*i) + (dt*j/numAct));
            MStime t2 = t1 + 50;

            // create UDP instances and set ID and time
            UDP u1 = UDP(10,8); u1.setID(current_hive->get_id()); u1.setTime(t1);
            UDP u2 = UDP(10,8); u2.setID(current_hive->get_id()); u2.setTime(t2);

            int b = (3*i + 7*j) % 10;   // board for activity to occur on (0 - 9)
            int s = (3*i + 5*j) % 4;    // inner sensor for activity (0 - 3)

            unsigned int num = dre() % 10; // random number
            unsigned int compare; // number to compare num to to determine if an entrance or exit occurred
            if (t1.getTmp()->tm_hour > 5 && t1.getTmp()->tm_hour < 10) compare = 7; // more exits in morning
            else if (t1.getTmp()->tm_hour > 16 && t1.getTmp()->tm_hour < 21) compare = 1; // more entrances in afternoon
            else compare = 4; // equal rates other times

            if (num > compare) {   // entrance
                u1.setTripped(b,7-s);
                uc->addMessage(u1);

                u2.setTripped(b,s);
                uc->addMessage(u2);
            }
            else {                      // exit
                u1.setTripped(b,s);
                uc->addMessage(u1);

                u2.setTripped(b,7-s);
                uc->addMessage(u2);
            }

            //            current_hive->add_udp(u1);
            //            current_hive->add_udp(u2);

            u1.~UDP();
            u2.~UDP();
            t1.~MStime();
            t2.~MStime();
        }
    }
    return uc;
}

// run that makes it likely to create a swarm (very similar to run)
UDPContainer* Simulation::runSwarm(){
    UDPContainer* uc = new UDPContainer();

    // for now the Time is just the current time
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    MStime t = MStime(localtime(&now));
    t.getTmp()->tm_hour=0; t.getTmp()->tm_min=0; t.getTmp()->tm_sec=0;

    // making factors that effect actuvuty
    int pop = current_hive->getPop();
    double kconst = 0.05; // constant conversion factor

    poisson_distribution<unsigned int> pois(static_cast<unsigned int>(pop * kconst)); // number of activities this time step determined by ks and pop
    unsigned long dt = 600000; // change in time in milliseconds
    for (unsigned int i = 0; i < (24*60*60*1000/dt); i++) { // loops through 24 hours
        unsigned int numAct = pois(dre);

        for (unsigned int j = 0; j < numAct; j++){
            MStime t1 = t + (dt*i + dt*j/numAct);
            MStime t2 = t1 + 50;

            UDP u1 = UDP(10,8); u1.setID(current_hive->get_id()); u1.setTime(t1);
            UDP u2 = UDP(10,8); u2.setID(current_hive->get_id()); u2.setTime(t2);

            unsigned int num = dre();

            int b = (3*i + 7*j) % 10; // board for activity to occur on (0 - 9)
            int s = (3*i + 5*j) % 4; // inner sensor for activity (0 - 3)

            if (num % 10 < 1) { // entrance
                u1.setTripped(b,7-s);
                uc->addMessage(u1);

                u2.setTripped(b,s);
                uc->addMessage(u2);
            }
            else { // exit
                u1.setTripped(b,s);
                uc->addMessage(u1);

                u2.setTripped(b,7-s);
                uc->addMessage(u2);
            }

            //            current_hive->add_udp(u1);
            //            current_hive->add_udp(u2);

            u1.~UDP();
            u2.~UDP();
            t1.~MStime();
            t2.~MStime();
        }
    }
    return uc;
}
