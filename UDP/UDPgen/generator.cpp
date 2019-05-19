#include "generator.h"

Generator::Generator(string file_name, int seed)
{
    this->seed = seed;
    this->file_name = file_name;

    try{
        ifstream input(file_name);
        int line;

        if(!input.is_open()){
            cout << "Error opening file" << endl;
            exit(EXIT_FAILURE);
        }
        while (!input.eof()){
            input >> line;
            lambdas.push_back(line);
        }
    }
    catch (exception &e) {
        cerr << e.what();
        exit(EXIT_FAILURE);
    }
}

// Generate no of gates tripped per hour
vector<int> Generator::generate(){
    vector<int> gates_each_hour;
    cout << endl;
    default_random_engine rng(seed);
    for (unsigned i = 0; i<lambdas.size();i++) {
        poisson_distribution<int> pois(lambdas.at(i));
        int no_of_gates = pois(rng);
        gates_each_hour.push_back(no_of_gates);
    }

    return gates_each_hour;
}

void Generator::print_times(){
    for (unsigned i = 0; i<times.size(); i++) {
        cout << times.at(i) << endl;
    }
}
