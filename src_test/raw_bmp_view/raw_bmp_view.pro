QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raw_bmp_view
TEMPLATE = app


SOURCES += main.cpp\
    rawbmpwidget.cpp \
    raw_bmp.cpp

HEADERS  += mainwindow.h \
    rawbmpwidget.h \
    raw_bmp.h
