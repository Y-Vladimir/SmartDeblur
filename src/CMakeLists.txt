project(SmartDeblur)

cmake_minimum_required(VERSION 2.8)

#------------------------------------------------------------------------------
# CPack
#
include(CPack)

#------------------------------------------------------------------------------
# Additional Qt libraries
#
set(QT_USE_QT3SUPPORT TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTWEBKIT TRUE)
set(QT_USE_QTXML TRUE)

#------------------------------------------------------------------------------
# Find Qt
#
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})


#------------------------------------------------------------------------------
# SmartDeblur UI
#
set(SmartDeblur_UI_SRCS
  HelpDialog.ui
  MainWindow.ui
  )

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
# FFTW
#
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

add_subdirectory(Models)

#------------------------------------------------------------------------------
# SmartDeblur executable
#
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

install(TARGETS SmartDeblur
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

#------------------------------------------------------------------------------
# Copy libfftw3.dll file to install/bin in Windows
#
if(WIN32)
  string(REPLACE ".lib" ".dll" FFTW_LIBRARY_DLL ${FFTW_LIBRARIES})
  install(FILES ${FFTW_LIBRARY_DLL}
    DESTINATION bin
	)
endif()
