#-------------------------------------------------
#
# Project created by QtCreator 2012-05-19T18:47:06
#
#-------------------------------------------------

QT       += core gui network xml

TARGET = SmartDeblur
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    DeconvolutionTool.cpp \
    WorkerThread.cpp \
    ImageUtils.cpp \
    MathUtlis.cpp \
    HelpDialog.cpp \
    CheckUpdatesThread.cpp

HEADERS  += MainWindow.h \
    FFTW/fftw3.h \
    DeconvolutionTool.h \
    WorkerThread.h \
    ImageUtils.h \
    Models/Blur.h \
    Models/FocusBlur.h \
    Models/MotionBlur.h \
    MathUtlis.h \
    Models/ProcessingContext.h \
    HelpDialog.h \
    Models/GaussianBlur.h \
    CheckUpdatesThread.h

FORMS    += MainWindow.ui \
    HelpDialog.ui

win32: LIBS += -L$$PWD/FFTW/libs/ -llibfftw3-3
unix:  LIBS +=  -L$$/usr/lib/ -lfftw3_threads -lfftw3

INCLUDEPATH += $$PWD/FFTW
DEPENDPATH += $$PWD/FFTW

RESOURCES += \
    MainResources.qrc

RC_FILE = SmartDeblur.rc
#CONFIG += console
