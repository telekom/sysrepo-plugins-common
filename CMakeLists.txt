cmake_minimum_required(VERSION 3.0.0)
project(srpc C)

SET(
    SRPC_SOURCES

    src/srpc/ly_tree.c
    src/srpc/common.c
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")
find_package(LIBYANG REQUIRED)
find_package(SYSREPO REQUIRED)

include_directories(src)
include_directories(${LIBYANG_INCLUDE_DIRS})
include_directories(${SYSREPO_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SRPC_SOURCES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})