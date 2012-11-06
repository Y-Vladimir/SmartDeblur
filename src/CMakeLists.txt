project(SmartDeblur)

cmake_minimum_required(VERSION 2.8)
include(CPack)

set(QT_USE_QT3SUPPORT TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTWEBKIT TRUE)
set(QT_USE_QTXML TRUE)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})


set(SmartDeblur_UI_SRCS
  HelpDialog.ui
  MainWindow.ui
  )

add_subdirectory(Models)

set(SmartDeblur_SRCS
  CheckUpdatesThread.cpp
  CheckUpdatesThread.h
  DeconvolutionTool.cpp
  DeconvolutionTool.h
  HelpDialog.cpp
  HelpDialog.h
  ImageUtils.cpp
  ImageUtils.h
  MainWindow.cpp
  MainWindow.h
  WorkerThread.cpp
  WorkerThread.h
  main.cpp
  )

set(SmartDeblur_MOC_H
  CheckUpdatesThread.h
  DeconvolutionTool.h
  HelpDialog.h
  MainWindow.h
  WorkerThread.h
  )

set(SmartDeblur_RESOURCES
  MainResources.qrc
  )

QT4_WRAP_UI(SmartDeblur_UI_CXX ${SmartDeblur_UI_SRCS})
QT4_WRAP_CPP(SmartDeblur_MOC_SRCS ${SmartDeblur_MOC_H})
QT4_ADD_RESOURCES(SmartDeblur_QRC_SRCS ${SmartDeblur_RESOURCES})

#------------------------------------------------------------------------------
# fftw
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/FFTW)

set(USE_SYSTEM_FFTW OFF
      CACHE BOOL
	  "Use system FFTW")
include(External_FFTW)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${FFTW_INCLUDES}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${QT_INCLUDES}
  )

add_executable(SmartDeblur
  ${Models_SRCS}
  ${SmartDeblur_MOC_H}
  ${SmartDeblur_MOC_SRCS}
  ${SmartDeblur_QRC_SRCS}
  ${SmartDeblur_SRCS}
  ${SmartDeblur_UI_CXX}
  )

add_dependencies(SmartDeblur FFTW)
target_link_libraries(SmartDeblur
  ${FFTW_LIBRARIES}
  ${QT_LIBRARIES}
  )

INSTALL(TARGETS SmartDeblur
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
