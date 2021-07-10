//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#ifndef GH_SYSTEMVERIOLG_DPI_LOGIC_VECTOR_HPP
#define GH_SYSTEMVERIOLG_DPI_LOGIC_VECTOR_HPP

#include <svdpi.h>

namespace gh {
namespace systemverilog {
namespace dpi {

class logic
{
public:
    typedef svLogicVecVal* vector_type;

    explicit logic(svLogic l)
    : _M_l(l), _M_v(0)
    { }

    logic(svLogicVecVal* v, int i)
    : _M_v(v), _M_i(i)
    { }

    svLogic operator()() const
    {
        if (_M_v)
        { return svGetBitselLogic(_M_v, _M_i); }
        else
        { return _M_l; }
    }

    logic& operator=(svLogic l)
    {
        _M_l = l;
        if (_M_v)
        { svPutBitselLogic(_M_v, _M_i, _M_l); }
        return *this;
    }

    logic& operator=(const logic& o)
    {
        if (this != &o)
        {
            _M_l = o._M_l;
            _M_v = o._M_v;
            _M_i = o._M_i;
        }
        return *this;
    }

private:
    svLogic _M_l;
    svLogicVecVal* _M_v;
    int _M_i;
};

class logic_vector
{
public:
    explicit logic_vector(svLogicVecVal* v)
    : _M_v(v)
    { }

    const logic
    operator[](int i) const
    { return logic(_M_v, i); }

    logic
    operator[](int i)
    { return logic(_M_v, i); }

private:
    svLogicVecVal* _M_v;
};

} // dpi
} // namespace systemverilog
} // namespace gh

#endif // GH_SYSTEMVERIOLG_DPI_LOGIC_VECTOR_HPP