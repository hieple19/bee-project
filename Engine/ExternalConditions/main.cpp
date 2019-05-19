#include <iostream>

using namespace std;

#include "ExternalConditions.h"

int main()
{


    cout << "creating ExternalConditions..." << endl;

    ExternalConditions * ec = new ExternalConditions();

    cout << "ExternalConditions created" << endl;

    cout << "setting temperature to 86 degrees..." << endl;

    ec->setTemp(86);

    cout << "temperature:" << endl;

    cout << ec->getTemp() << endl;


    cout << "setting season to summer..." << endl;

    ec->setSeason(ExternalConditions::summer);

    cout << "season:" << endl;

    cout << ec->getSeason() << endl;

    cout << "destroying ExternalConditions..." << endl;

    delete ec;

    cout << "ExternalConditions destroyed" << endl;

    return 0;
}

