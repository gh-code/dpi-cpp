//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#ifndef GH_SYSTEMVERIOLG_DPI_VERSION_HPP
#define GH_SYSTEMVERIOLG_DPI_VERSION_HPP

#include <svdpi.h>

namespace gh {
namespace systemverilog {
namespace dpi {

inline
const char*
version()
{ return svDpiVersion(); }

} // dpi
} // namespace systemverilog
} // namespace gh

#endif // GH_SYSTEMVERIOLG_DPI_VERSION_HPP