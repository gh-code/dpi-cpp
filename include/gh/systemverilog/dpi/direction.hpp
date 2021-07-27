//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#ifndef GH_SYSTEMVERIOLG_DPI_DIRECTION_HPP
#define GH_SYSTEMVERIOLG_DPI_DIRECTION_HPP

#include <svdpi.h>

namespace gh {
namespace systemverilog {
namespace dpi {

template<class T>
class input
{
public:
    typedef T   value_type;
    typedef T*  pointer;
    typedef T&  reference;

public:
    explicit input(const reference v)
    : value(v)
    { }

    operator value_type() const
    { return value; }

private:
    const reference value;
};

template<class T>
class inout
{
public:
    typedef T  value_type;
    typedef T* pointer;
    typedef T& reference;

public:
    explicit inout(pointer v)
    : value(v)
    { }

    operator value_type() const
    { return *value; }

    void operator=(value_type v)
    { *value = v; }

private:
    pointer value;
};

template<class T>
class output
{
public:
    typedef T   value_type;
    typedef T*  pointer;
    typedef T&  reference;

public:
    explicit output(pointer v)
    : value(v)
    {}

    void operator=(value_type v)
    { *value = v; }

private:
    pointer value;
};

} // dpi
} // namespace systemverilog
} // namespace gh

#endif // GH_SYSTEMVERIOLG_DPI_DIRECTION_HPP