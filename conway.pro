#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29 15:41:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = conway
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamewidget.cpp \
    patterns.cpp

HEADERS  += mainwindow.h \
    gamewidget.h \
    patterns.h

FORMS    += mainwindow.ui \
    patterns.ui

OTHER_FILES += \
    README.markdown

DISTFILES += \
    stylesheet.qss \
    image/1.png \
    image/1.png \
    image/10.png \
    image/11.png \
    image/12.png \
    image/2.png \
    image/3.png \
    image/4.png \
    image/5.png \
    image/6.png \
    image/7.png \
    image/8.png \
    image/9.png

RESOURCES +=
