CONFIG += qt
QT += network
QT += xml
LIBS += -lfftw3_threads -lfftw3 -lm

SOURCES = CheckUpdatesThread.cpp  DeconvolutionTool.cpp  HelpDialog.cpp  ImageUtils.cpp  main.cpp  MainWindow.cpp  MathUtlis.cpp  WorkerThread.cpp
HEADERS = CheckUpdatesThread.h  DeconvolutionTool.h  HelpDialog.h  ImageUtils.h  MainWindow.h  MathUtlis.h  WorkerThread.h \
	Models/Blur.h  Models/FocusBlur.h  Models/GaussianBlur.h  Models/MotionBlur.h  Models/ProcessingContext.h 
FORMS = HelpDialog.ui  MainWindow.ui
RESOURCES = MainResources.qrc
TARGET = smartdeblur
