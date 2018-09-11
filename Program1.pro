TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    reader.cpp \
    dstring.cpp \
    classification.cpp \
    tests.cpp

HEADERS += \
    reader.h \
    dstring.h \
    classification.h \
    catch.hpp
