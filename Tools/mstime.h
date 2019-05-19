// Class to represent date and time for UDP messages
// library tm struct stores all information except milliseconds

#ifndef MSTIME_H
#define MSTIME_H

#include <ctime>
#include <chrono>
#include <iostream>
#include <string>

class MStime{
public:
    MStime(tm*,unsigned long i=0);
    MStime();
    MStime(const MStime& m);
    void setMS(unsigned long);
    void setTM(tm*);
    tm* getTmp() {return tmp;}
    unsigned int getMS() {return ms;}

    double operator-(const MStime& other);      // returns the difference in milliseconds of two times
    MStime operator+(const unsigned long i);    // adds a number of milliseconds to a time and creates another time
    MStime operator=(const MStime& other);
    std::string toString();
private:
    tm* tmp;
    unsigned long ms;
};

#endif // MSTIME_H
