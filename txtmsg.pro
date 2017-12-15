TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    message.cpp

DISTFILES += \
    examplemsg.xml \
    formatting.txt \
    Readme.txt

HEADERS += \
    message.h
