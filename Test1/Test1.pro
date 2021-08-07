QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractiterator.cpp \
    basevector.cpp \
    camera.cpp \
    canvas.cpp \
    framebuffer.cpp \
    heightsmap.cpp \
    heightsmappoints.cpp \
    main.cpp \
    mainwindow.cpp \
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
    camera.h \
    canvas.h \
    constiterator.h \
    constiterator.hpp \
    errors.h \
    framebuffer.h \
    heightsmap.h \
    heightsmappoints.h \
    iterator.h \
    iterator.hpp \
    mainwindow.h \
    point.h \
    triangularpolygon.h \
    tripolmas.h \
    vector.h \
    vector.hpp \
    zbuffer.h \
    zbufferalg.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
