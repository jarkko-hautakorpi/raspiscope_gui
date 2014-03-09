QT       += core gui
QT       += widgets serialports

TARGET = Qt4raspiscope2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scopesetupwindow.cpp \
    serialdatalink.cpp \
    hdlc.cpp

#SUBDIRS += src
INCLUDEPATH += /usr/include/qwt
#LIBS += -l qwt-qt4
LIBS += -l qwt

# IN RASPBERRY PI
INCLUDEPATH += /usr/include/qwt-qt4


HEADERS  += mainwindow.h \
    scopesetupwindow.h \
    serialdatalink.h \
    datalink_commands.h \
    defined_serial_commands.h \
    hdlc.h

FORMS    += \
    mainwindow.ui \
    scopesetupwindow.ui


CONFIG += serialport
