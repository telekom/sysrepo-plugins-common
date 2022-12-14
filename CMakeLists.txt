#
# Copyright (c) 2022 Deutsche Telekom AG.
#
# This source code is licensed under BSD 3-Clause License (the "License").
# You may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://opensource.org/licenses/BSD-3-Clause
#
# SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
# SPDX-FileContributor: Sartura Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause
#
cmake_minimum_required(VERSION 3.0.0)
project(srpc VERSION 0.1.0 LANGUAGES C)

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

add_library(${PROJECT_NAME} SHARED ${SRPC_SOURCES})

# project version
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

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