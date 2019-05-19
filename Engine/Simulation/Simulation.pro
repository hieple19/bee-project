TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    simulation.cpp \
    ../ExternalConditions/ExternalConditions.cpp \
    ../Configuration/configuration.cpp \
    ../BusyBeeEngine/hive.cpp \
    ../BusyBeeEngine/run.cpp \
    #../../UDP/UDPgen/generator.cpp \
    ../../Tools/mstime.cpp \
    ../../Tools/udp.cpp \
    ../../Tools/udpcontainer.cpp \
    ../../Tools/activity.cpp \
    ../../Tools/activitygen.cpp

HEADERS += \
    simulation.h \
    ../ExternalConditions/ExternalConditions.h \
    ../Configuration/configuration.h \
    ../BusyBeeEngine/hive.h \
    ../BusyBeeEngine/run.h \
    #../../UDP/UDPgen/generator.h \
    ../../Tools/mstime.h \
    ../../Tools/udp.h \
    ../../Tools/udpcontainer.h \
    ../../Tools/activity.h \
    ../../Tools/activitygen.h
