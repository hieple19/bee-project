#include "udpcontainer.h"

using namespace std;

// default contructor
UDPContainer::UDPContainer(){
}

// constructs the container with the contents of the inputFile
UDPContainer::UDPContainer(string inputFile){
    readFile(inputFile);
}

// adds the contents of inputFile to the end of the container
void UDPContainer::readFile(string inputFile){
    ifstream in(inputFile); // file to read from
    string line;

    // check for error opening file
    if(!in.is_open()) {
          perror("Error open");
          exit(EXIT_FAILURE);
    }

    // read lines of the file and add to the container
    while(getline(in, line)) {
        addMessage(UDP(line));
    }

    in.close();
}

// writes the contents of this UDP container to the given output file
void UDPContainer::writeFile(string outputFile){
    ofstream out(outputFile); // file to write to
    string line;

    // check for error opening file
    if(!out.is_open()) {
          perror("Error open");
          exit(EXIT_FAILURE);
    }

    unsigned long long max = messages.size();
    for (unsigned long i = 0; i < max; i++) {
        out << messages.at(i).toString() << endl; // write each UDP string on a line
    }

    out.close();
}

// add a single UDP to the container
void UDPContainer::addMessage(UDP u){
    messages.push_back(u);
}

// prints the contents of this UDP container to the std out for debugging
void UDPContainer::print(){
    unsigned long long max = messages.size();
    for (unsigned long i = 0; i < max; i++) {
        cout << messages.at(i).toString() << endl;
    }
}

// sort the UDP messages in this container by time
void UDPContainer::timeSort(){
    timeSort(0,messages.size() - 1);
}

// sort the UDP messages in this container by time
// currently not called anywhere but could be helpful in the future
void UDPContainer::timeSort(unsigned long long leftBound, unsigned long long rightBound){
    unsigned long left = leftBound;
    unsigned long right = rightBound - 1;
    unsigned long mid = (leftBound + rightBound) / 2; // used to choose pivot

    if (rightBound > leftBound) { // if the list is length 1 it doesn't need sorting
        UDP pivot = messages.at(mid);
        udpSwap(mid,rightBound); // swaps the pivot to the end of the list

        while (left <= right) { // partitioning of the list. allows left and right to cross
            while (messages.at(left) < pivot) {
                left++; // moves inward. ends up at first spot in right half
            }
            while (right >= left && messages.at(right) >= pivot){
                right--; // moves inward. ends up at last spot in left half
            }
            if (right > left) {
                udpSwap(left,right); // swaps left and right to partition
            }
        }
        udpSwap(rightBound,left); // the pivot is at rightBound, so it gets moved to its spot

        if (leftBound < left - 1) {
            timeSort(leftBound,left - 1); // calls sort on left half
        }
        if (rightBound > left + 1) {
            timeSort(left + 1,rightBound); // calls sort on right half
        }
    }
}

// swaps two UDP messages in this UDPContainer
void UDPContainer::udpSwap(unsigned long one, unsigned long two){
    UDP temp = messages.at(one);
    messages.at(one) = messages.at(two);
    messages.at(two) = temp;
}

// finds if any entrences/exits occured within time interval dt (in milliseconds)
// assumes paired UDP messages are sorted by time
ActivityLog* UDPContainer::findActivity(int dt){
    cout << "Searching UDPContainer for activity" << endl; // useful for debugging

    unsigned long long size = messages.size();
    ActivityLog* al = new ActivityLog;

    // loop through all UDP instances
    for (unsigned long i = 0; i < size - 1; i++){
        UDP current = messages.at(i); // current UDP instance

        // looping from current UDP through the next 10 messages (limitting to 10 speeds up performance significantly)
        for (unsigned long j = i; j < i + 10 && j < size; j++){
            UDP next = messages.at(j); // UDP instance being compared to current

            if (current.getID() != next.getID()) continue; // make sure the hives are the same
            double timeDif = next - current;
            if (timeDif > dt || timeDif < 0) continue; // make sure the time difference isn't too big or negative

            // get the needed variables in advance of the loops so they aren't called every iteration
            bool** cTripped = current.getTripped();
            bool** nTripped = next.getTripped();
            int boards = current.getNumBoards();
            int sensors = current.getNumSensors();

            // loop through all boards and sensors
            for (int b = 0; b < boards; b++){
                for (int s = 0; s < sensors; s++){

                    // if first one sensor, then the corresponding sensor are tripped, record the activity
                    if (cTripped[b][s] && nTripped[b][(sensors-1) - s]){
                        if (s < 4) al->addAct(current.getID(), false, current.getTime());
                        else al->addAct(current.getID(),true, current.getTime());
                    }

                } // end s loop
            } // end b loop
        } // end j loop
    } // end i loop

    return al;
}

// + operator concatonates the vectors of UDPContainers
UDPContainer UDPContainer::operator+(const UDPContainer &uc){
    unsigned long long size = uc.getSize();

    for (unsigned long i = 0; i < size; i++){
        messages.push_back(uc.messages.at(i));
    }

    return *this;
}
