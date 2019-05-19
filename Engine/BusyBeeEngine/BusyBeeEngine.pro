TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    busybeeengine.cpp \
    ../OutputController/outputcontroller.cpp \
    ../Configuration/configuration.cpp \
    ../ExternalConditions/ExternalConditions.cpp \
    ../../DBee/sqlite3.c \
    ../../DBee/dbtool.cpp \
    ../../DBee/dbtable.cpp \
    ../../DBee/dbtablerun.cpp \
    ../../Tools/mstime.cpp \
    ../../Tools/udp.cpp \
    ../../Tools/udpcontainer.cpp \
    ../../Tools/activity.cpp \
    ../../Tools/activitygen.cpp \
    ../Simulation/simulation.cpp \
    runhistory.cpp \
    run.cpp \
    hive.cpp

HEADERS += \
    busybeeengine.h \
    ../OutputController/outputcontroller.h \
    ../Configuration/configuration.h \
    ../ExternalConditions/ExternalConditions.h \
    ../../DBee/sqlite3.h \
    ../../DBee/sqlite3ext.h \
    ../../DBee/dbtool.h \
    ../../DBee/dbtable.h \
    ../../DBee/dbtablerun.h \
    ../../Tools/mstime.h \
    ../../Tools/udp.h \
    ../../Tools/udpcontainer.h \
    ../../Tools/activity.h \
    ../../Tools/activitygen.h \
    ../Simulation/simulation.h \
    runhistory.h \
    run.h \
    hive.h

#LIBS += -l sqlite3
LIBS += -pthread
#LIBS += -ldl

QMAKE_CXXFLAGS += -std=gnu++0x -pthread
QMAKE_CFLAGS += -std=gnu++0x -pthread

