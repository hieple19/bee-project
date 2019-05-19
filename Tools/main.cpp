#include <iostream>
#include "udpcontainer.h"

using namespace std;

int main() {
    UDPContainer cont("input.txt"); // read in UDP messages from input file to a UDPContainer (needs to be in the build folder)
    cont.print();
    //cout << "Sorting" << endl;
    //cont.timeSort();
    //cont.writeFile("output.txt"); // write from UDPContainer to output file
    //cont.print(); // print from UDPContianer to stdout

    ActivityLog* al = cont.findActivity(500); // find entrances and exists, allowing 1 second between sensors
    al->print(); // print the ActivityLog contents


//    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
//    MStime t1 = MStime(localtime(&now)); t1.setMS(0);
//    MStime t2 = t1; t2.setMS(800);
//    MStime t3 = t1 + 1357;

//    cout << t1.toString() << t2.toString() << t3.toString() << endl;


}
