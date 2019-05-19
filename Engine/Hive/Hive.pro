TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    hive.cpp

HEADERS += \
    hive.h \

SOURCES += ../../Tools/mstime.cpp
HEADERS += ../../Tools/mstime.h
