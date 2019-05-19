#include "analyzer.h"

Analyzer::Analyzer()
{
}

bool Analyzer::analyze_swarm(int original_population, PopulationHistory *event) {
    int swarm_pop = original_population*0.4;
    return event->population < swarm_pop;


}

void Analyzer::analyzeAlerts() {

    // analyze alerts

}
