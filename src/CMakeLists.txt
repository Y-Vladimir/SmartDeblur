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
set(FFTW_VERSION 3.3.2)
set(FFTW_MD5 "6977ee770ed68c85698c7168ffa6e178")
set(FFTW_URL_PRE "ftp://ftp.fftw.org/pub/fftw/fftw-")
set(FFTW_URL_POST ".tar.gz")
set(FFTW_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/fftw/install)
set(FFTW_LIBRARIES_PATH ${FFTW_INSTALL_DIR}/lib/)
set(FFTW_LIBRARIES
  ${FFTW_LIBRARIES_PATH}${CMAKE_STATIC_LIBRARY_PREFIX}fftw3${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${FFTW_LIBRARIES_PATH}${CMAKE_STATIC_LIBRARY_PREFIX}fftw3_threads${CMAKE_STATIC_LIBRARY_SUFFIX})

include(ExternalProject)
ExternalProject_Add( FFTW
  URL ${FFTW_URL_PRE}${FFTW_VERSION}${FFTW_URL_POST}
  URL_MD5 ${FFTW_MD5}
  SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/fftw/src
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/fftw/src
  INSTALL_DIR ${FFTW_INSTALL_DIR}
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --enable-threads
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${FFTW_INSTALL_DIR}/include
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
