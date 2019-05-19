TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    configuration.cpp \
    ../BusyBeeEngine/hive.cpp \
    ../../Tools/mstime.cpp \
    ../../Tools/udp.cpp \
    ../../Tools/udpcontainer.cpp \
    ../../Tools/activity.cpp \
    ../../Tools/activitygen.cpp \

HEADERS += \
    configuration.h \
    ../BusyBeeEngine/hive.h \
    ../../Tools/mstime.h \
    ../../Tools/mstime.h \
    ../../Tools/udp.h \
    ../../Tools/udpcontainer.h \
    ../../Tools/activity.h \
    ../../Tools/activitygen.h
