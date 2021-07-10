//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#ifndef GH_SYSTEMVERIOLG_DPI_VECTOR_HPP
#define GH_SYSTEMVERIOLG_DPI_VECTOR_HPP

#include <svdpi.h>
#include <gh/systemverilog/dpi/logic.hpp>

namespace gh {
namespace systemverilog {
namespace dpi {

template<class Scalar>
class vector
{
public:
    vector()
    : _M_v(0)
    { }

    explicit vector(typename Scalar::vector_type v)
    : _M_v(v)
    { }

    const Scalar
    operator[](int i) const
    { return Scalar(_M_v, i); }

    Scalar
    operator[](int i)
    { return Scalar(_M_v, i); }

private:
    typename Scalar::vector_type _M_v;
};

} // dpi
} // namespace systemverilog
} // namespace gh

#endif // GH_SYSTEMVERIOLG_DPI_VECTOR_HPP