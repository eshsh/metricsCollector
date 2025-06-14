set(MODULE_NAME simple_example)

add_executable(${MODULE_NAME} simple_example.cpp)

target_link_libraries(${MODULE_NAME} PRIVATE metricslib)
