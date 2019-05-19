#include <iostream>
#include "generator.h"
using namespace std;

#include <string>
#include <bitset>
#include <ctime>

/*
HC0002-D18.12.19T13.43.16000-B0B1B16B0B0B0B0B0B0B0
    HC0002: device ID for the hive from which the UDP originates
    D18.12.19T13.43.16000: date and time
    B0B1B16B0B0B0B0B0B0B0: status of boards. The B chars are dividers between boards. The example message indicates that boards 2 and and 3 show activity on sensors 1 and 5 respectively.
    B0B0B0B160B0B0B0B0B0B0: here's another example, indicating that board 4 shows activity on sensors 6 and 8.
    B0B0B0B0B0B0B0B0B0B4: here's another example, indicating that board 10 shows activity on sensor 3.
*/


int main()
{
    Generator gates_data_generator("activityLevels.txt",1234);
    int num_of_boards = 10;
    int num_of_gates = 8;


    // inputs (would all be contained in one UDP struct)

    // long representing ID of the hive
    long hiveID = 205;

    // gets the current time and puts in a struct tm*
    time_t timer = time(nullptr); time_t* timerP = &timer;
    tm* t = localtime(timerP);

    // bool array saying whether or not [board-1][gate-1] was tripped
    bool** gatesTripped = new bool*[num_of_boards]; // indexes 0-9 represent board 1-10
    for (int i = 0; i<10; i++) {
        gatesTripped[i] = new bool[num_of_gates]; // typically 8 gates (1-8) on each board
        for (int j=0;j<8;j++) gatesTripped[i][j] = false;
    }


    vector<int> gates_data = gates_data_generator.generate();

    // Loops through all gate data
    for(unsigned i = 0; i<gates_data.size(); i++){
        cout << i << endl;
        // Reset the gates tripped variable
        for(int board = 0; board<num_of_boards; board++){
            for (int gate=0; gate<num_of_gates; gate++) gatesTripped[board][gate] = false;
        }

        string s = "HC"; s+= to_string(hiveID);

        int no_gates_tripped = gates_data.at(i);
        cout << "Num gates tripped " << no_gates_tripped << endl;

        // Generate random board and gate numbers
        // Entry/exit not correspond yet
        // Time stamp for entry/exit is not done
        // Gate and corresponding gate are tripped at the same time
        // To be dealt with later
        for(int j = 0; j<no_gates_tripped; j++){
            int board = rand() % num_of_boards;
            int gate = rand() % num_of_gates;

            int corr_gate = num_of_gates + 1 - gate;
            // Avoid overlapping of gate numbers
            while(gatesTripped[board][gate]){
                board = rand() % num_of_boards;
                gate = rand() % num_of_gates;
                corr_gate = num_of_gates + 1 - gate;
            }
            gatesTripped[board][gate] = true;
            gatesTripped[board][corr_gate] = true;
        }


        // Time variable is hard coded to start from 0
        // Update when more info is decided
        s += "-D"; s += to_string(t->tm_mday); s += "."; s += to_string(t->tm_mon);
        s += "."; s += to_string(t->tm_year - 100); s += "T"; s += to_string(0+i);
        s += "."; s += to_string(t->tm_min); s += "."; s += to_string(t->tm_sec * 1000);

        s += "-";

        // adding information about the board
        for (int a = 0; a < num_of_boards; a++){
            s += "B";
            bool* gates = gatesTripped[a];
            int num = 0;
            for (int b = 0; b < num_of_gates; b++){
                if (gates[b]) num += (1 << b);
            }
            s += to_string(num);
        }

        cout << s << endl << endl;
    }

    return 0;
}

