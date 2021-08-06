TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        abstractiterator.cpp \
        basevector.cpp \
        heightsarray.cpp \
        heightsmap.cpp \
        heightsmappoints.cpp \
        main.cpp \
        point.cpp \
        triangularpolygon.cpp \
        tripolmas.cpp \
        zbuffer.cpp

HEADERS += \
    abstractiterator.h \
    baseiterator.h \
    baseiterator.hpp \
    basevector.h \
    constiterator.h \
    constiterator.hpp \
    errors.h \
    heightsarray.h \
    heightsmap.h \
    heightsmappoints.h \
    iterator.h \
    iterator.hpp \
    point.h \
    triangularpolygon.h \
    tripolmas.h \
    vector.h \
    vector.hpp \
    zbuffer.h
