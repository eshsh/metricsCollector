set(MODULE_NAME custom_logger_example)

include(FetchContent)

#spdlog
FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.14.1.tar.gz)
FetchContent_MakeAvailable(spdlog)
unset(CMAKE_SUPPRESS_DEVELOPER_WARNINGS)

add_executable(${MODULE_NAME} custom_logger.cpp)

target_include_directories(${MODULE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${MODULE_NAME} PRIVATE metricslib spdlog)
