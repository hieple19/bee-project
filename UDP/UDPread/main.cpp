#include <iostream>

using namespace std;

#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define boardnb 10

struct UDP{
    int id;
    tm* t;
    bool** gatesTripped;
};

vector<UDP> messages;


UDP loadInput(string input);

/*
HC0002-D18.12.19T13.43.16000-B0B1B16B0B0B0B0B0B0B0
    HC0002: device ID for the hive from which the UDP originates
    D18.12.19T13.43.16000: date and time
    B0B1B16B0B0B0B0B0B0B0: status of boards. The B chars are dividers between boards. The example message indicates that boards 2 and and 3 show activity on sensors 1 and 5 respectively.
    B0B0B0B160B0B0B0B0B0B0: here's another example, indicating that board 4 shows activity on sensors 6 and 8.
    B0B0B0B0B0B0B0B0B0B4: here's another example, indicating that board 10 shows activity on sensor 3.
*/

int main() {
    string inputFile = "input.txt";

    ifstream myFile(inputFile);
    string line;
    // check for error opening file
    if(!myFile.is_open()) {
          perror("Error open");
          exit(EXIT_FAILURE);
    }

    // for each line, load information
    vector<UDP> messages;
    while(getline(myFile, line)) {
        messages.push_back(loadInput(line));
    }

    // now we have a vector with every element is a udp message deconstructed
    return 0;
}

// parses the UDP formatted string input and returns a UDP struct with the data
UDP loadInput(string input) {
    istringstream iss(input);
    char* s = new char[50];
    iss.getline(s,5,'C'); // get rid of the leading HC

    iss.getline(s,10,'-'); // extract the hive ID
    int id = atoi(s);

    iss.get(); // get rid of D
    iss.getline(s,5,'.'); int day = atoi(s);
    iss.getline(s,5,'.'); int month = atoi(s);
    iss.getline(s,5,'T'); int year = atoi(s) + 100; // years since 1900

    iss.getline(s,5,'.'); int hours = atoi(s);
    iss.getline(s,5,'.'); int minutes = atoi(s);
    iss.getline(s,5,'-'); int seconds = atoi(s) / 1000; // converts milliseconds to seconds

    // initialize all bools to false
    bool** gatesTripped = new bool*[boardnb];
    for (int i = 0; i<boardnb; i++) {
        gatesTripped[i] = new bool[8]; // typically 8 gates (1-8) on each board
        for (int j=0;j<8;j++) gatesTripped[i][j] = false;
    }

    iss.get(); // get rid of first B
    for (int i = 0; i < boardnb; i++){
        if (i < boardnb - 1) iss.getline(s, 10, 'B'); // dont get line the last time
        int temp = atoi(s);

        for(int j = 0; j < 8 && temp > 0; j++){
            if(temp % (1 << j)){
                gatesTripped[i-1][j-1] = true;
            }
        }
    }


    // construct the UDP struct and fill it with the extracted data
    UDP message;

    message.id = id;
    tm* datetime = new tm;
    datetime->tm_mday = day; datetime->tm_mon = month; datetime->tm_year = year;
    datetime->tm_hour = hours; datetime->tm_min = minutes; datetime->tm_sec = seconds;
    message.t = datetime;
    message.gatesTripped = gatesTripped;

    return message;
}

