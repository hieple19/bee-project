// container class for UDP messages
// can be constructed by reading a text file or print its contents to a file or std out
// can search its contents to determine entrances and exits from hives

#ifndef UDPCONTAINER_H
#define UDPCONTAINER_H

#include "udp.h"
#include "activity.h"
#include <vector>
#include <iostream>
#include <fstream>

class UDPContainer {
public:
    UDPContainer();
    UDPContainer(std::string);

    void readFile(std::string);
    void writeFile(std::string);
    void print();

    void timeSort();
    void timeSort(unsigned long long,unsigned long long);
    void addMessage(UDP);
    ActivityLog* findActivity(int);
    UDPContainer operator+(const UDPContainer &uc);
    unsigned long long getSize() const {return messages.size();}
private:
    std::vector<UDP> messages;
    void udpSwap(unsigned long,unsigned long);
};

#endif // UDPCONTAINER_H
