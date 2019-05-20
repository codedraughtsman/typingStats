#-------------------------------------------------
#
# Project created by QtCreator 2018-10-11T11:22:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    textentrywidget.cpp \
    texteditlogger.cpp \
    choosetestdialog.cpp \
    analyticsdialog.cpp \
    testmanager.cpp \
    testdata.cpp \ 
    keyevent.cpp \
    testresult.cpp \
    lasttestanalyticwidget.cpp \
    storagemanager.cpp \
    abstracttextentrywidget.cpp \
    textentryovertypewidget.cpp \
    targettextmanager.cpp


HEADERS += \
        mainwindow.h \
    textentrywidget.h \
    texteditlogger.h \
    choosetestdialog.h \
    analyticsdialog.h \
    testmanager.h \
    testdata.h \
    keyevent.h \
    testresult.h \
    lasttestanalyticwidget.h \
    storagemanager.h \
    abstracttextentrywidget.h \
    textentryovertypewidget.h \
    targettextmanager.h

FORMS += \
    choosetestdialog.ui \
    analyticsdialog.ui \ 
    lasttestanalyticwidget.ui
