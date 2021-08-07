TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        abstractiterator.cpp \
        basevector.cpp \
        framebuffer.cpp \
        heightsarray.cpp \
        heightsmap.cpp \
        heightsmappoints.cpp \
        main.cpp \
        point.cpp \
        triangularpolygon.cpp \
        tripolmas.cpp \
        zbuffer.cpp \
        zbufferalg.cpp

HEADERS += \
    abstractiterator.h \
    baseiterator.h \
    baseiterator.hpp \
    basevector.h \
    constiterator.h \
    constiterator.hpp \
    errors.h \
    framebuffer.h \
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
    zbuffer.h \
    zbufferalg.h
