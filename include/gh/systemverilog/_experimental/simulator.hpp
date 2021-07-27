//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#ifndef GH_SYSTEMVERIOLG_SIMULATOR_HPP
#define GH_SYSTEMVERIOLG_SIMULATOR_HPP

#include <cstddef>
#include <cstdarg>
#include <svdpi.h>

namespace gh {
namespace systemverilog {

class simulator
{
public:

};

svOpenArrayHandle create(int dim, int left, int right, ...)
{
    size_t len = sizeof(void*) + (6 + (dim << 1)) * sizeof(int);
    char* impl = new char[len];
    char* pos = impl + sizeof(void*);
    *pos = dim; pos += sizeof(int);
    /*preserve*/ pos += sizeof(int);
    /*preserve*/ pos += sizeof(int);
    /*preserve*/ pos += sizeof(int);
    *pos = left; pos += sizeof(int);
    *pos = right; pos += sizeof(int);
    va_list vl;
    va_start(vl, right);
    int i;
    for (i = 1; i <= dim; ++i) {
        *pos = /* left  */ va_arg(vl, int); pos += sizeof(int);
        *pos = /* right */ va_arg(vl, int); pos += sizeof(int);
    }
    va_end(vl);
    return (void*) impl;
}

template<typename T>
int* alloc_arr(svOpenArrayHandle h, int& size)
{
    size = 1;
    for (int d = 1; d <= svDimensions(h); ++d)
        size *= svSize(h, d);
    *(T**) h = new T[size];
    return *(T**) h;
}

} // namespace systemverilog
} // namespace gh


#endif // GH_SYSTEMVERIOLG_SIMULATOR_HPP