TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        analyzer.cpp \
        ../Engine/BusyBeeEngine/hive.cpp \
        ../Tools/mstime.cpp \
        ../Tools/udp.cpp \
        ../Tools/udpcontainer.cpp \
        ../Tools/activity.cpp \
        ../Tools/activitygen.cpp \

#    ../Engine/BusyBeeEngine/runhistory.cpp \

HEADERS += \
    analyzer.h\
    ../Engine/BusyBeeEngine/hive.h \
     ../Tools/mstime.h \
    ../Tools/udp.h \
    ../Tools/udpcontainer.h \
    ../Tools/activity.h \
    ../Tools/activitygen.h \
