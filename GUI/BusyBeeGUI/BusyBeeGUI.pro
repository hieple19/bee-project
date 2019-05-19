#-------------------------------------------------
#
# Project created by QtCreator 2019-04-04T13:15:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = BusyBeeGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        busybeegui.cpp \
        ../../Engine/ExternalConditions/ExternalConditions.cpp \
    visualizegui.cpp \
    qcustomplot.cpp \
   ../../Engine/Simulation/simulation.cpp \
   ../../Tools/udpcontainer.cpp \
   ../../Tools/udp.cpp \
   ../../Tools/activity.cpp \
   ../../Engine/Configuration/configuration.cpp \
#   ../../UDP/UDPgen/generator.cpp \
   ../../Tools/mstime.cpp \
    ../../Engine/BusyBeeEngine/hive.cpp \
    ../../Engine/BusyBeeEngine/run.cpp \
    ../../Engine/BusyBeeEngine/runhistory.cpp \
    ../../Engine/BusyBeeEngine/busybeeengine.cpp \
    ../../DBee/sqlite3.c \
    ../../DBee/dbtool.cpp \
    ../../DBee/dbtable.cpp \
    ../../DBee/dbtablerun.cpp \
    ../../Engine/OutputController/outputcontroller.cpp \



HEADERS += \
        busybeegui.h \
        ../../Engine/ExternalConditions/ExternalConditions.h \
    visualizegui.h \
    qcustomplot.h \
    ../../Engine/Simulation/simulation.h \
    ../../Tools/udpcontainer.h \
    ../../Tools/udp.h \
    ../../Tools/activity.h \
    ../../Engine/Configuration/configuration.h \
    #../../UDP/UDPgen/generator.h \
    ../../Tools/mstime.h \
    ../../Engine/BusyBeeEngine/hive.h \
    ../../Engine/BusyBeeEngine/run.h \
    ../../Engine/BusyBeeEngine/runhistory.h \
    ../../Engine/BusyBeeEngine/busybeeengine.h \
    ../../DBee/sqlite3.h \
    ../../DBee/sqlite3ext.h \
    ../../DBee/dbtool.h \
    ../../DBee/dbtable.h \
    ../../DBee/dbtablerun.h \
    ../../Engine/OutputController/outputcontroller.h \

#LIBS += -l sqlite3
LIBS += -pthread
#LIBS += -ldl

FORMS += \
        busybeegui.ui \
    visualizegui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    busybeeguiresources.qrc \
    visualizeguiresources.qrc
