QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Iterators/abstractiterator.cpp \
    canvas.cpp \
    HeightsMap/heightsmap.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Errors/BaseError.h \
    Errors/HeightsMapErrors.h \
    Errors/IteratorErrors.h \
    Iterators/abstractiterator.h \
    Iterators/baseiterator.h \
    Iterators/baseiterator.hpp \
    Iterators/constiterator.h \
    Iterators/constiterator.hpp \
    Iterators/iterator.h \
    Iterators/iterator.hpp \
    canvas.h \
    HeightsMap/heightsmap.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
