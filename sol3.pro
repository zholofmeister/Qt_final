#-------------------------------------------------
#
# Project created by QtCreator 2020-12-19T18:43:01
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sol3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videosurface.cpp \
    solveimage.cpp

HEADERS  += mainwindow.h \
    ../sol5/videosurface.h \
    videosurface.h \
    solveimage.h

FORMS    += mainwindow.ui \
    solveimage.ui

RESOURCES += \
    img.qrc \
    translator.qrc

TRANSLATIONS  +=  resources/tr_zh.ts  \
        resources/tr_en.ts

