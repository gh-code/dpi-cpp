//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#ifndef SVDPI_HPP
#define SVDPI_HPP

#include "svdpi.h"
#include <iostream>

namespace sv {

struct convert_t { };
struct check_throw_t { };

const convert_t convert;
const check_throw_t check_throw;

struct bit
{
    svScalar value;
    bit() : value(sv_0) {}
    bit(svScalar s) : value(s) {}
    bit(svScalar s, convert_t) : value(s & 1) {}
    bit(svScalar s, check_throw_t) : value(s)
    {
        if (s >> 1)
            throw "bad bit value";
    }
    operator svScalar() { return value; }
};

struct logic
{
    svScalar value;
    logic() : value(sv_x) {}
    logic(svScalar s) : value(s) {}
    logic(svScalar s, convert_t) : value(s & 3) {}
    logic(svScalar s, check_throw_t) : value(s)
    {
        if (s >> 2)
            throw "bad bit value";
    }
    operator svScalar() { return value; }
};

inline std::ostream& operator<<(std::ostream& os, bit l)
{
    switch (l) {
        case sv_0: os << '0'; break;
        case sv_1: os << '1'; break;
        default:
            throw "bad bit value";
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, logic l)
{
    switch (l) {
        case sv_0: os << '0'; break;
        case sv_1: os << '1'; break;
        case sv_z: os << 'z'; break;
        case sv_x: os << 'x'; break;
        default:
            throw "bad logic value";
    }
    return os;
}

template<class T>
inline bool is_bit(T) { return false; }
template<>
inline bool is_bit(bit) { return true; }
template<class T>
inline bool is_logic(T) { return false; }
template<>
inline bool is_logic(logic) { return true; }

const svScalar _sv_0 = sv_0;
const svScalar _sv_1 = sv_1;
const svScalar _sv_z = sv_z;
const svScalar _sv_x = sv_x;

} // namespace sv

#undef sv_0
#undef sv_1
#undef sv_z
#undef sv_x

#define sv_0 sv::bit(sv::_sv_0)
#define sv_1 sv::bit(sv::_sv_1)
#define sv_z sv::logic(sv::_sv_z)
#define sv_x sv::logic(sv::_sv_x)

#undef svBit
#undef svLogic

#define svBit sv::bit
#define svLogic sv::logic

#endif // SVDPI_HPP
