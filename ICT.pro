#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T14:30:13
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialt.cpp \
    dialogc.cpp \
    dialr.cpp \
    registers.cpp \
    dials.cpp \
    udpcomm.cpp \
    dialcomm.cpp \
    dialposplot.cpp \
    dialtorplot.cpp \
    dialquit.cpp \
    plotdata.cpp \
    threadStarter.cpp \
    sequenceplot.cpp \
    serialcomm.cpp

HEADERS  += mainwindow.h \
    dialt.h \
    dialogc.h \
    dialr.h \
    registers.h \
    config.h \
    dials.h \
    udpcomm.h \
    dialcomm.h \
    dialposplot.h \
    dialtorplot.h \
    dialquit.h \
    plotdata.h \
    threadStarter.h \
    sequenceplot.h \
    serialcomm.h

FORMS    += mainwindow.ui \
    dialt.ui \
    dialogc.ui \
    dialr.ui \
    dialm.ui \
    dials.ui \
    dialcomm.ui \
    dialtorplot.ui \
    dialposplot.ui \
    dialquit.ui \


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../qwt-6.1.0/lib/ -lqwt
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../qwt-6.1.0/lib/ -lqwtd
#else:unix: LIBS += -L$$PWD/../../../../qwt-6.1.0/lib/ -lqwt

#INCLUDEPATH += $$PWD/../../../../qwt-6.1.0/include
#DEPENDPATH += $$PWD/../../../../qwt-6.1.0/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../qwt-6.1.0/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../qwt-6.1.0/lib/ -lqwtd
else:unix: LIBS += -L$$PWD/../../../../../qwt-6.1.0/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../qwt-6.1.0/include
DEPENDPATH += $$PWD/../../../../../qwt-6.1.0/include
