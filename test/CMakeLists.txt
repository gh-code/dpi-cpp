#
# Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/gh-code/dpi-cpp
#

include_directories(include)

file(GLOB SOURCES "*.cpp")
add_executable(gh_systemverilog-tests
    ${SOURCES}
    src/svdpi.cpp
)