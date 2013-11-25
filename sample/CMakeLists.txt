
cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

project(wlcpp_sample)

add_definitions(-Wall --std=c++11)

find_package(WaylandClient REQUIRED)
include_directories(${WaylandClient_INCLUDE_DIRS})

find_package(Doxygen)

add_executable(wlcpp_sample
    main.cpp
    display.hpp
    display.cpp
    event_queue.hpp
    event_queue.cpp
    proxy.hpp
    proxy.cpp
    wlcpp.hpp
    wlcpp.cpp
)

target_link_libraries(wlcpp_sample
    ${WaylandClient_LIBRARIES}
)

if(DOXYGEN_EXECUTABLE)
    configure_file(Doxyfile.in
        Doxyfile
        @ONLY
    )

    add_custom_command(
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        OUTPUT ${PROJECT_BINARY_DIR}/html/index.html
        DEPENDS Doxyfile
        DEPENDS proxy.hpp event_queue.hpp wlcpp.hpp display.hpp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_custom_target(doc
        DEPENDS ${PROJECT_BINARY_DIR}/html/index.html
        SOURCES Doxyfile
    )
endif()

