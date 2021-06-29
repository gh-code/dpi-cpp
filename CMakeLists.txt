#
# Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/gh-code/dpi-cpp
#

cmake_minimum_required(VERSION 3.7)

project(main)

#aux_source_directory(. DIR_SRC)
include_directories (include)

set (CMAKE_CXX_STANDARD 11)

add_executable (main
    main.cpp
    src/svdpi.c
)