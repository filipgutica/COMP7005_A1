#-------------------------------------------------
#
# Project created by QtCreator 2015-09-22T17:53:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = COMP7005_A1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    downloader.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    downloader.h

FORMS    += mainwindow.ui \
    dialog.ui \
    downloader.ui
