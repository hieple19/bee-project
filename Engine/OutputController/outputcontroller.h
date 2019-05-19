#ifndef OUTPUTCONTROLLER_H
#define OUTPUTCONTROLLER_H

#include <string>
using namespace std;

#include "../Configuration/configuration.h"
#include "../BusyBeeEngine/hive.h"
class Configuration;

class OutputController
{
public:
    OutputController();
    OutputController(Configuration* figs);
    void bootleg(string path); // export
    void bootleg(); // export
private:
    Configuration* configuration; // instance of Configuration
    // DBee database
};

#endif // OUTPUTCONTROLLER_H
