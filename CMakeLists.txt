cmake_minimum_required(VERSION 3.16)
project(metricsCollector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTING "Build tests" ON)

add_subdirectory(examples)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

set(FILES
    include/istat.h
    include/statscheduler.h
    include/statistics/cpustatistics.h
    include/statistics/httpstatistic.h
    include/statistics/networkstatistic.h
    include/filewrapper.h
    include/filelogger.h
    include/consolelogger.h
    include/statistics.h

    src/statscheduler.cpp
    src/filewrapper.cpp
    src/statistics.cpp
)

add_library(metricslib STATIC ${FILES})

target_include_directories(metricslib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)
install(TARGETS metricslib
    EXPORT metricslibTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT metricslibTargets
    FILE metricslibTargets.cmake
    NAMESPACE metricslib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/metricslib
)
