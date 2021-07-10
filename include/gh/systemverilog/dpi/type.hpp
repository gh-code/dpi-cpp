//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#ifndef GH_SYSTEMVERIOLG_DPI_TYPE_HPP
#define GH_SYSTEMVERIOLG_DPI_TYPE_HPP

#include <svdpi.h>

namespace gh {
namespace systemverilog {

struct byte_t      { using value_type = char; };
struct shortint_t  { using value_type = short int; };
struct int_t       { using value_type = int; };
struct longint_t   { using value_type = long long; };
struct real_t      { using value_type = double; };
struct shortreal_t { using value_type = float; };
struct chandle_t   { using value_type = void*; };
struct string_t    { using value_type = const char*; };
struct bit_t       { using value_type = unsigned char; };
struct logic_t     { using value_type = unsigned char; };
struct reg_t       { using value_type = unsigned char; };

} // namespace systemverilog
} // namespace gh


#endif // GH_SYSTEMVERIOLG_DPI_TYPE_HPP