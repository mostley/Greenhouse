VPATH += ../shared
INCLUDEPATH += ../shared

HEADERS       = glwidget.h \
    mainwindow.h \
    ComputeAlgorithm.h \
    Blob.h \
    qtmodel.h \
    marching.h \
    stlwriter.h \
    triangle.h \
    gardener.h \
    fertilizer.h \
    potatofertilizer.h \
    qcube.h
SOURCES       = glwidget.cpp \
                main.cpp \
    mainwindow.cpp \
    qtmodel.cpp \
    marching.cpp \
    stlwriter.cpp \
    triangle.cpp \
    gardener.cpp \
    fertilizer.cpp \
    potatofertilizer.cpp \
    qcube.cpp
QT           += opengl widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl
INSTALLS += target

contains(QT_CONFIG, opengles.) {
    contains(QT_CONFIG, angle): \
        warning("Qt was built with ANGLE, which provides only OpenGL ES 2.0 on top of DirectX 9.0c")
    error("This example requires Qt to be configured with -opengl desktop")
}

FORMS += \
    mainwindow.ui
