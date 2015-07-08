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
    drivers/escposprinter.cpp \
    drivers/generichidscanner.cpp \
    drivers/linuxusb.cpp \
    drivers/linuxusbhid.cpp \
    controller.cpp

HEADERS += \
    connection.h \
    tcpserver.h \
    drivers/errors.h \
    drivers/escposcommands.h \
    drivers/escposprinter.h \
    drivers/generichidscanner.h \
    drivers/hidtable.h \
    drivers/iticketprinter.h \
    drivers/itransport.h \
    drivers/linuxusb.h \
    drivers/linuxusbhid.h \
    controller.h
