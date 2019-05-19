#include "busybeegui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Configuration* c = new Configuration();
    //ExternalConditions* ec = new ExternalConditions();
    //Hive* hi = new Hive();
    //
    //Simulation* s = new Simulation(c,ec,hi);
    //
    //UDPContainer uc2 = s->run2();
    //uc2.print();
    //
    //uc2.writeFile("dataforslim.txt");
    //ActivityLog *al = uc2.findActivity(100);
    //al->print();
    QApplication a(argc, argv);
    BusyBeeGUI w;
    w.show();

    return a.exec();
}
