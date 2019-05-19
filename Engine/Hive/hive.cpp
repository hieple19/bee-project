#include "hive.h"

/* constructor for Hive */
Hive::Hive() {

}

/* setter for int size */
void Hive::setSize(int s) {
    size = s;
}

/* getter for int size */
int Hive::getSize() {
    return size;
}

/* setter for int nBoards -- number of boards */
void Hive::setNBoards(int boards) {
    nBoards = boards;
}

/* getter for int nBoards -- number of boards */
int Hive::getNBoards() {
    return nBoards;
}
