#include <iostream>
#include "simulation.h"

using namespace std;

int main(){
    Configuration* c = new Configuration();
    ExternalConditions* ec = new ExternalConditions(); // can include temp and season
    Hive* hi = new Hive(); hi->setPop(10000); // includes hive population
    ec->setTemp(50); ec->setSeason(0); ec->setWeather(1);

    Simulation* s = new Simulation(c,ec,hi);

    cout << endl << endl << endl;
    UDPContainer* uc2 = s->run();
    uc2->print();

    //uc2.writeFile("dataforslim.txt");
    ActivityLog *al = uc2->findActivity(100);
    al->print();

    return 0;
}

