QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Array/AbstractArray.cpp \
    Canvas.cpp \
    HeightsMap/HeightsMap.cpp \
    HeightsMap/HeightsMapPoints.cpp \
    HeightsMap/Point.cpp \
    Iterator/AbstractIterator.cpp \
    Matrix/AbstractMtrx.cpp \
    Triangles/TriPolArray.cpp \
    Triangles/TriangularPolygon.cpp \
    Vector/AbstractVector.cpp \
    ZBuffer/FrameBuffer.cpp \
    ZBuffer/ZBuffer.cpp \
    ZBuffer/ZBufferAlg.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Array/AbstractArray.h \
    Array/BaseArray.h \
    Array/BaseArray.hpp \
    Canvas.h \
    Errors/ArrayErrors.h \
    Errors/BaseError.h \
    Errors/HeightsMapErrors.h \
    Errors/HeightsMapPointsErrors.h \
    Errors/IteratorErrors.h \
    Errors/MtrxErrors.h \
    Errors/VectorErrors.h \
    HeightsMap/HeightsMap.h \
    HeightsMap/HeightsMapPoints.h \
    HeightsMap/Point.h \
    Iterator/AbstractIterator.h \
    Iterator/BaseIterator.h \
    Iterator/BaseIterator.hpp \
    Iterator/ConstIterator.h \
    Iterator/ConstIterator.hpp \
    Iterator/Iterator.h \
    Iterator/Iterator.hpp \
    Matrix/AbstractMtrx.h \
    Matrix/BaseMtrx.h \
    Matrix/BaseMtrx.hpp \
    Triangles/TriPolArray.h \
    Triangles/TriangularPolygon.h \
    Vector/AbstractVector.h \
    Vector/Vector.h \
    Vector/Vector.hpp \
    ZBuffer/FrameBuffer.h \
    ZBuffer/ZBuffer.h \
    ZBuffer/ZBufferAlg.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
