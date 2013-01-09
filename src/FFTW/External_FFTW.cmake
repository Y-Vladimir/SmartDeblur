#
# Encapsulates building FFTW as an External Project.

set(msg "ATTENTION: You have enabled the use of fftw,")
set(msg "${msg} this library is distributed under a GPL license.")
set(msg "${msg} By enabling this option, the binary of SmartDeblur")
set(msg "${msg} that you are going to build will be covered by a GPL license,")
set(msg "${msg} and so it will be any executable that you link against these libraries.")
message("${msg}")

set(FFTW_THREADS_CONFIGURATION --enable-threads)

#--Some influential environment variables:
#--  CC          C compiler command
#--  CFLAGS      C compiler flags
#--  LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
#--              nonstandard directory <lib dir>
#--  LIBS        libraries to pass to the linker, e.g. -l<library>
#--  CPPFLAGS    C/C++/Objective C preprocessor flags, e.g. -I<include dir> if
#--              you have headers in a nonstandard directory <include dir>
#-- set(ENV{CC}       "${CMAKE_C_COMPILER}")
#-- set(ENV{CFLAGS}   "${CMAKE_C_FLAGS} ${OPENMP_FLAG}")
#-- set(ENV{LDFLAGS}  "${CMAKE_C_FLAGS} ${OPENMP_FLAG}")
#-- set(ENV{LIBS}     "${CMAKE_EXE_LINKER_FLAGS} ${OPENMP_FLAG}")
#-- set(ENV{CPPFLAGS} "${CMAKE_C_FLAGS} ${OPENMP_FLAG}")

## Perhaps in the future a set of TryCompiles could be used here.
set(FFTW_OPTIMIZATION_CONFIGURATION "" CACHE INTERNAL "architecture flags: --enable-sse --enable-sse2 --enable-altivec --enable-mips-ps --enable-cell")
if(USE_SYSTEM_FFTW)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
  find_package(FFTW REQUIRED COMPONENTS double threads)
else()
  set(FFTW_COMPILER_FLAGS
    CC=${CMAKE_C_COMPILER}
    CXX=${CMAKE_CXX_COMPILER}
    CFLAGS=${CMAKE_C_FLAGS}
    CXXFLAGS=${CMAKE_CXX_FLAGS})

  if(WIN32 AND NOT MINGW)
    message("Can't build fftw as external project on Windows")
    message("Using pre-compiled fftw library")
	  set(FFTW_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/FFTW/libs/libfftw3-3.lib)
	  set(FFTW_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/FFTW)
  else()
    #
    # fftw limitation -- can't be built in
    # a directory with whitespace in its name.
    if(${CMAKE_CURRENT_BINARY_DIR} MATCHES ".*[ \t].*")
      message(FATAL_ERROR
        "Can't build fftw in a directory with whitespace in its name")
    endif()
    set(FFTW_SHARED_FLAG --enable-shared)
  	set(FFTW_VERSION 3.3.2)
  	set(FFTW_MD5 "6977ee770ed68c85698c7168ffa6e178")
  	set(FFTW_URL_PRE "ftp://ftp.fftw.org/pub/fftw/fftw-")
  	set(FFTW_URL_POST ".tar.gz")
  	set(FFTW_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/fftw/install)
  	set(FFTW_LIBRARIES_PATH ${FFTW_INSTALL_DIR}/lib/)
  	set(FFTW_LIBRARIES
      ${FFTW_LIBRARIES_PATH}${CMAKE_SHARED_LIBRARY_PREFIX}fftw3${CMAKE_SHARED_LIBRARY_SUFFIX}
      ${FFTW_LIBRARIES_PATH}${CMAKE_SHARED_LIBRARY_PREFIX}fftw3_threads${CMAKE_SHARED_LIBRARY_SUFFIX})

    include(ExternalProject)
  	ExternalProject_add(FFTW
  	  URL ${FFTW_URL_PRE}${FFTW_VERSION}${FFTW_URL_POST}
  	  URL_MD5 ${FFTW_MD5}
  	  SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/fftw/src
        BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/fftw/src
        INSTALL_DIR ${FFTW_INSTALL_DIR}
  	  UPDATE_COMMAND ""
  	  CONFIGURE_COMMAND <SOURCE_DIR>/configure
  	    ${FFTW_SHARED_FLAG}
  	    ${FFTW_OPTIMIZATION_CONFIGURATION}
  	    ${FFTW_THREADS_CONFIGURATION}
  	    --disable-fortran
  	    --prefix=<INSTALL_DIR>
  	    ${FFTW_COMPILER_FLAGS}
  	)

    set(FFTW_INCLUDES ${FFTW_INSTALL_DIR}/include)
  endif()
endif()
