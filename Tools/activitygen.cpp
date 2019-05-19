#include "activitygen.h"

ActivityGen::ActivityGen(string file_name, int seed) {
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
vector<int> ActivityGen::generate(){
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

void ActivityGen::print_times(){
    for (unsigned i = 0; i<times.size(); i++) {
        cout << times.at(i) << endl;
    }
}


//void ActivityGen::generate_data(int duration){
//    // Reset the gates tripped variable
//    for(int board = 0; board<num_of_boards; board++){
//        for (int gate=0; gate<num_of_gates; gate++) gatesTripped[board][gate] = false;
//    }

//    for(int j = 0; j<no_gates_tripped; j++){
//        int board = rand() % num_of_boards;
//        int gate = rand() % num_of_gates;

//        int corr_gate = num_of_gates + 1 - gate;
//        // Avoid overlapping of gate numbers
//        while(gatesTripped[board][gate]){
//            board = rand() % num_of_boards;
//            gate = rand() % num_of_gates;
//            corr_gate = num_of_gates + 1 - gate;
//        }
//        gatesTripped[board][gate] = true;
//        gatesTripped[board][corr_gate] = true;
//    }
//}

void ActivityGen::config_gen(int board_num, int gate_num){
    this->num_of_gates = gate_num;
    this->num_of_boards = board_num;
}
