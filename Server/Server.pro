#-------------------------------------------------
#
# Project created by QtCreator 2015-01-16T08:15:08
#
#-------------------------------------------------

QT       += core network widgets

LIBS += -L/usr/lib/$$system(uname -i)-linux-gnu
LIBS += -lusb

QT       -= gui

TARGET = Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += /usr/include

SOURCES += main.cpp \
    connection.cpp \
    tcpserver.cpp \
    controller.cpp

HEADERS += \
    connection.h \
    tcpserver.h \
    controller.h \
    posdriverinterface.h
