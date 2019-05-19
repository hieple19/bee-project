#ifndef ANALYZER_H
#define ANALYZER_H

#include "../Engine/BusyBeeEngine/hive.h"

class Analyzer
{
public:
    Analyzer();
    bool analyze_swarm(int original_population, PopulationHistory *event);
    void analyzeAlerts();
private:

    int runID;
};

#endif // ANALYZER_H
