TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    token_parser.cpp

DISTFILES += \
    input.txt

HEADERS += \
    token_parser.h
