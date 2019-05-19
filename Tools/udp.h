// Class to store the information contained in a UDP string
// Can be constructed by parsing a string or format itself as a string, as well as other utility functions

#ifndef UDP_H
#define UDP_H

#include <cmath>
#include <string>
#include <sstream>
#include "mstime.h"


class UDP {
public:
    UDP(int,int);
    UDP(std::string);

    void setTripped(int i,int j) {sensorsTripped[i][j] = true;}
    void setUntripped(int i,int j) {sensorsTripped[i][j] = false;}
    void setID(int id) {hiveID = id;}
    void setTime(MStime time) {t = new MStime(time);}

    int getID() {return hiveID;}
    MStime* getTime() const {return t;}
    bool** getTripped() {return sensorsTripped;}
    int getNumBoards() {return numBoards;}
    int getNumSensors() {return numSensors;}

    double operator-(const UDP& u);
    bool operator<(const UDP& u);
    bool operator>(const UDP& u);
    bool operator<=(const UDP& u);
    bool operator>=(const UDP& u);

    std::string toString();
private:
    int numBoards; // number of boards for this hive
    int numSensors; // number of sensors on each board
    int hiveID;
    MStime* t;
    bool** sensorsTripped;
};

#endif // UDP_H
