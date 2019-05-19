TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    ../Engine/BusyBeeEngine/run.cpp \
    ../Engine/BusyBeeEngine/runhistory.cpp \
    ../Engine/OutputController/outputcontroller.cpp \
    ../Engine/Configuration/configuration.cpp \
    ../Engine/ExternalConditions/ExternalConditions.cpp \
        sqlite3.c \
        dbtable.cpp \
        dbtool.cpp \
    dbtablerun.cpp \
    dbtablestatus.cpp \
    dbtableudp.cpp \
    dbtablehive.cpp \
    ../Tools/mstime.cpp \
    ../Tools/udp.cpp \
    ../Tools/udpcontainer.cpp \
    ../Tools/activity.cpp \
    ../Tools/activitygen.cpp \
    ../Engine/BusyBeeEngine/hive.cpp \

HEADERS += \
        sqlite3.h \
        sqlite3ext.h \
    ../Engine/BusyBeeEngine/run.h \
    ../Engine/BusyBeeEngine/runhistory.h \
    ../Engine/OutputController/outputcontroller.h \
    ../Engine/Configuration/configuration.h \
    ../Engine/ExternalConditions/ExternalConditions.h \
        dbtable.h \
        dbtool.h \
    dbtablerun.h \
    dbtablestatus.h \
    dbtableudp.h \
    dbtablehive.h \
     ../Tools/mstime.h \
    ../Tools/udp.h \
    ../Tools/udpcontainer.h \
    ../Tools/activity.h \
    ../Tools/activitygen.h \
    ../Engine/BusyBeeEngine/hive.h \

#LIBS += -l sqlite3
LIBS += -pthread
#LIBS += -ldl

QMAKE_CXXFLAGS += -std=gnu++0x -pthread
QMAKE_CFLAGS += -std=gnu++0x -pthread
