//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#include <svdpi.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

const char* svDpiVersion()
{
    return "1.0";
}

int svDimensions(svOpenArrayHandle h)
{
    return *(int*)((char*) h + sizeof(void*));
}

int svLeft(const svOpenArrayHandle h, int d)
{
    return *(int*)((char*) h + sizeof(void*) + (2 * d + 4) * sizeof(int));
}

int svRight(const svOpenArrayHandle h, int d)
{
    return *(int*)((char*) h + sizeof(void*) + (2 * d + 5) * sizeof(int));
}

int svIncrement(const svOpenArrayHandle h, int d)
{
    // if type is dynamic array, return -1
    return (svLeft(h, d) >= svRight(h, d) ? 1 : -1);
}

int svLow(const svOpenArrayHandle h, int d)
{
    return (svIncrement(h, d) == -1 ? svLeft(h, d) : svRight(h, d));
}

int svHigh(const svOpenArrayHandle h, int d)
{
    return (svIncrement(h, d) == -1 ? svRight(h, d) : svLeft(h, d));
}

int svSize(svOpenArrayHandle h, int d)
{
    return svHigh(h, d) - svLow(h, d) + 1;
}

void* svGetArrayPtr(const svOpenArrayHandle h)
{
    return (void*)(*(int**)h);
}

void* svGetArrElemPtr(svOpenArrayHandle h, int index, ...)
{
    va_list args;
    va_start(args, index);
    int d;
    int p = 1;
    for (d = 2; d <= svDimensions(h); ++d)
        p *= svSize(h, d);

    if (index < svLow(h, 1) || index > svHigh(h, 1))
        return NULL;
    int offset = (index - svLow(h, 1)) * p;
    // printf("[1]: %d\n", index);
    for (d = 2; d <= svDimensions(h); ++d)
    {
        int i = va_arg(args, int);
        // printf("[%d]: %d\n", d, i);
        if (i < svLow(h, d) || i > svHigh(h, d))
            return NULL;
        p /= svSize(h, d);
        offset += (i - svLow(h, d)) * p;
    }
    va_end(args);
    return (void*)(*(int**)h + offset);
}

void* svGetArrElemPtr1(svOpenArrayHandle h, int index)
{
    if (index < svLow(h, 1) || index > svHigh(h, 1))
        return NULL;
    int offset = index - svLow(h, 1);
    return (void*)(*(int**)h + offset);
}

void* svGetArrElemPtr2(svOpenArrayHandle h, int index1, int index2)
{
    if (index1 < svLow(h, 1) || index1 > svHigh(h, 1) ||
        index2 < svLow(h, 2) || index2 > svHigh(h, 2))
        return NULL;
    int offset = (index1 - svLow(h, 1)) * svSize(h, 2)
               + (index2 - svLow(h, 2));
    return (void*)(*(int**)h + offset);
}

void* svGetArrElemPtr3(svOpenArrayHandle h, int index1, int index2, int index3)
{
    if (index1 < svLow(h, 1) || index1 > svHigh(h, 1) ||
        index2 < svLow(h, 2) || index2 > svHigh(h, 2) ||
        index3 < svLow(h, 3) || index3 > svHigh(h, 3))
        return NULL;
    int offset = (index1 - svLow(h, 1)) * svSize(h, 3) * svSize(h, 2)
               + (index2 - svLow(h, 2)) * svSize(h, 3)
               + (index3 - svLow(h, 3));
    return (void*)(*(int**)h + offset);
}