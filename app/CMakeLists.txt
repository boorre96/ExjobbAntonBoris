#-------------------------------------------------------------------------------
# Zephyr Example Application
#
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Project build
project(app)

# From nanopb
nanopb_generate_cpp(proto_sources proto_headers RELPATH .
    src/simple.proto
)

# We need to be able to include generated header files
zephyr_library_include_directories(${CMAKE_CURRENT_BINARY_DIR})


configure_file(app_version.h.in ${CMAKE_BINARY_DIR}/app/include/app_version.h)
target_include_directories(app PRIVATE ${CMAKE_BINARY_DIR}/app/include src)


if(CONFIG_ZTEST)
    target_sources(app PRIVATE ${proto_sources})
    target_include_directories(app PRIVATE
        ${ZEPHYR_BASE}/include   
    tests/bmi160_test/src)
    target_sources(app PRIVATE tests/bmi160_test/src/test_bmi160.c)

else()
    target_sources(app PRIVATE ${proto_sources} src/main.c)
endif()