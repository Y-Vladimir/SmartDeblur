#-------------------------------------------------
#
# Project created by QtCreator 2012-05-19T18:47:06
#
#-------------------------------------------------

QT       += core gui

TARGET = SmartDeblur
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    DeconvolutionTool.cpp \
    WorkerThread.cpp \
    ImageUtils.cpp

HEADERS  += MainWindow.h \
    FFTW/fftw3.h \
    DeconvolutionTool.h \
    WorkerThread.h \
    ImageUtils.h \
    Models/Blur.h \
    Models/FocusBlur.h \
    Models/MotionBlur.h

FORMS    += MainWindow.ui

win32: LIBS += -L$$PWD/FFTW/libs/ -llibfftw3-3

INCLUDEPATH += $$PWD/FFTW
DEPENDPATH += $$PWD/FFTW

RESOURCES += \
    MainResources.qrc

RC_FILE = SmartDeblur.rc
