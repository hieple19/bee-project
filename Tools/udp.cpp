#include "udp.h"

using namespace std ;

// constructs this UDP class with the given numbers of boards and sensors
UDP::UDP(int boards,int sensors){
    numBoards = boards;
    numSensors = sensors;

    sensorsTripped = new bool*[numBoards]; // indexes 0-9 represent board 1-10
    for (int i = 0; i < boards; i++) {
        sensorsTripped[i] = new bool[numSensors]; // typically 8 gates (1-8) on each board
        for (int j = 0; j < sensors; j++) sensorsTripped[i][j] = false; // initiallize every sensor to not tripped
    }

    hiveID = 0;
}

// constructs a UDP instance from the given UDP string (assumes 10 boards with 8 sensors each)
UDP::UDP(string s) : UDP(10,8) {
    istringstream iss(s); // uses a string stream to parse the UDP string
    char* c = new char[10];

    // HiveID
    iss.getline(c,5,'C'); // get rid of the leading HC
    iss.getline(c,10,'-'); setID(atoi(c)); // extract the hive ID

    // Date
    tm* tmp = new tm;
    iss.getline(c,10,'D'); // get rid of D
    iss.getline(c,10,'.'); tmp->tm_mday = atoi(c);
    iss.getline(c,10,'.'); tmp->tm_mon = atoi(c) - 1; // tm struct months index 0-11
    iss.getline(c,10,'T'); tmp->tm_year = atoi(c) + 100; // years since 1900

    // Time
    iss.getline(c,10,'.'); tmp->tm_hour = atoi(c);
    iss.getline(c,10,'.'); tmp->tm_min = atoi(c);
    iss.getline(c,10,'-'); int ms = atoi(c); tmp->tm_sec = ms / 1000; // converts milliseconds to seconds
    t = new MStime(tmp, ms % 1000); // stores the milliseconds independently

    // Board sensors
    iss.getline(c,10,'B'); // get rid of first B
    for (int i = 0; i < numBoards; i++){
        if ((i + 1) < numBoards) iss.getline(c, 10, 'B'); // dont do the last time
        else iss.getline(c,10);

        int temp = atoi(c); // the number between the Bs

        // find which sensors on the board were tripped
        for (int j = numSensors - 1; j >= 0; j--){
            if (temp >= exp2(j)){
                setTripped(i,j);
                temp -= exp2(j);
            }
        } // end j
    } // end i
}

// finds the difference in times of UDP messages
// positive when this UDP is after u
double UDP::operator-(const UDP &u){
    return t - u.getTime();
}

// return true if this UDP time stamp is earlier than u's
bool UDP::operator<(const UDP &u){
    return *this - u < 0;
}

bool UDP::operator<=(const UDP &u){
    return *this - u <= 0;
}

// return true if this UDP time stamp is later than u's
bool UDP::operator>(const UDP &u) {
    return *this - u > 0;
}

bool UDP::operator>=(const UDP &u){
    return *this - u >= 0;
}

// converts this UDP class to a UDP formatted string
string UDP::toString(){
    char* c = new char[10];

    // hive information
    sprintf(c,"%04u",hiveID); // give hiveID leading 0s
    string s = "HC"; s += string(c);

    // date/time information
    s += t->toString();

    // board sensor information
    for (int a = 0; a < numBoards; a++){
        s += "B";
        bool* gates = sensorsTripped[a];
        int num = 0;
        for (int b = 0; b < numSensors; b++){
            if (gates[b]) num += exp2(b);
        }
        s += to_string(num);
    }

    return s;
}
