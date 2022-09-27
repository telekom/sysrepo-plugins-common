cmake_minimum_required(VERSION 3.0.0)
project(srpc C)

include(GNUInstallDirs)

include(CompileOptions.cmake)

SET(
    SRPC_SOURCES

    src/srpc/ly_tree.c
    src/srpc/common.c
    src/srpc/feature_status.c
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")
find_package(LIBYANG REQUIRED)
find_package(SYSREPO REQUIRED)

include_directories(src)
include_directories(deps/uthash/include)
include_directories(${LIBYANG_INCLUDE_DIRS})
include_directories(${SYSREPO_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SRPC_SOURCES})

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    FILES ${PROJECT_SOURCE_DIR}/src/srpc.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES
    ${PROJECT_SOURCE_DIR}/src/srpc/ly_tree.h
    ${PROJECT_SOURCE_DIR}/src/srpc/common.h
    ${PROJECT_SOURCE_DIR}/src/srpc/feature_status.h
    ${PROJECT_SOURCE_DIR}/src/srpc/types.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/srpc
)

add_custom_target(uninstall COMMAND xargs rm < ${PROJECT_SOURCE_DIR}/build/install_manifest.txt)

if(ENABLE_TESTS)
    find_package(CMOCKA REQUIRED)
    include(CTest)
    include(test/Tests.cmake)
endif()