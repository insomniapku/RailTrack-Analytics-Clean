QT += core gui widgets

TARGET = TripPlanner
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    core/Time.cpp \
    core/City.cpp \
    core/Railway.cpp \
    core/Trip.cpp \
    core/Statistics.cpp\
    reportdialog.cpp\
    addtripdialog.cpp

HEADERS += \
    mainwindow.h \
    core/Time.h \
    core/City.h \
    core/Railway.h \
    core/Trip.h \
    core/Statistics.h\
    reportdialog.h\
    addtripdialog.h

FORMS += \
    mainwindow.ui\
    addtripdialog.ui\
    reportdialog.ui

RESOURCES += resources.qrc
