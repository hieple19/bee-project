#include <iostream>
#include "hive.h"

using namespace std;

int main()
{
    cout << "creating hive..." << endl;

    Hive * myHive = new Hive;

    cout << "hive created" << endl;

    cout << "setting size to 50..." << endl;

    myHive->setSize(50);

    cout << "size:" << endl;

    cout << myHive->getSize() << endl;

    cout << "setting number of boards to 6..." << endl;

    myHive->setNBoards(6);

    cout << "number of boards:" << endl;

    cout << myHive->getNBoards() << endl;

    cout << "destroying hive..." << endl;

    delete myHive;

    cout << "hive destroyed" << endl;

    return 0;
}
