TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    udp.cpp \
    #activitygen.cpp \
    udpcontainer.cpp \
    activity.cpp \
    mstime.cpp

HEADERS += \
    udp.h \
    #activitygen.h \
    udpcontainer.h \
    activity.h \
    mstime.h \
    mstime.h
