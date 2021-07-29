TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        abstractiterator.cpp \
        heightsarray.cpp \
        heightsmap.cpp \
        heightsmappoints.cpp \
        main.cpp \
        point.cpp

HEADERS += \
    abstractiterator.h \
    baseiterator.h \
    baseiterator.hpp \
    constiterator.h \
    constiterator.hpp \
    errors.h \
    heightsarray.h \
    heightsmap.h \
    heightsmappoints.h \
    iterator.h \
    iterator.hpp \
    point.h
