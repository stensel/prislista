#-------------------------------------------------
#
# Project created by QtCreator 2015-04-28T09:35:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prislista
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databasemanager.cpp \
    agreementdialog.cpp \
    pricelistdialog.cpp \
    supplierdialog.cpp

HEADERS  += mainwindow.h \
    databasemanager.h \
    agreementdialog.h \
    pricelistdialog.h \
    supplierdialog.h

FORMS    += mainwindow.ui \
    agreementdialog.ui \
    pricelistdialog.ui \
    supplierdialog.ui
