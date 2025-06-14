set(MODULE_NAME src)
set(SRC_FILES
    istat.h
    statscheduler.h
    statistics/cpustatistics.h
    statistics/httpstatistic.h
    statistics/networkstatistic.h

    statscheduler.cpp

)

add_library(${MODULE_NAME} STATIC ${SRC_FILES}
    filewrapper.h filewrapper.cpp
    filelogger.h
    consolelogger.h
    statistics.h
    statistics.cpp )

target_include_directories(${MODULE_NAME} PRIVATE
    ${INSTALL_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${MODULE_NAME} PRIVATE spdlog)
