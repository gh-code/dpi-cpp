//
// Copyright (c) 2021 Gary Huang (gh dot nctu at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/gh-code/dpi-cpp
//

#include <gh/systemverilog/dpi.hpp>
#include <gh/systemverilog/sim.hpp>

#include <string>
#include <cstdio>

namespace sv = gh::systemverilog;
using sv_int = gh::systemverilog::int_t;

extern "C" {

void dpi_func_0d(svOpenArrayHandle);
void dpi_func_1d(svOpenArrayHandle);
void dpi_func_2d(svOpenArrayHandle);
void dpi_func_4d(svOpenArrayHandle);

}

void dpi_func_4d(svOpenArrayHandle h)
{
    sv::openarray<sv_int,4> oa(h);
    printf("dimensions: %d\n", oa.dimensions());
    printf("%2d: [%d:%d]\n", 0, oa.type_left(), oa.type_right());
    printf("%2d: [%d:%d]\n", 1, oa.left(), oa.right());
    printf("%2d: [%d:%d]\n", 2, oa[1].left(), oa[1].right());
    printf("%2d: [%d:%d]\n", 3, oa[1][2].left(), oa[1][2].right());
    printf("%2d: [%d:%d]\n", 4, oa[1][2][3].left(), oa[1][2][3].right());
    printf("%2d: [%d:%d]\n", 3, oa.left(3), oa.right(3));
    for (int i = oa.low(); i <= oa.high(); ++i)
    {
       for (int j = oa[i].low(); j <= oa[i].high(); ++j)
           for (int k = oa[i][j].low(); k <= oa[i][j].high(); ++k)
               for (int l = oa[i][j][k].low(); l <= oa[i][j][k].high(); ++l)
                   printf("%d ", oa[i][j][k][l]);
        printf("\n");
    }
    printf("\n");
    oa[1][2][3][4];
    oa[1][2][3][4] = 4321;
    oa.at(1).at(2).at(3).at(4);
    oa.at(1).at(2).at(3).at(4) = 4321;

    int dim = svDimensions(h);
    printf("dimensions: %d\n", dim);
    for (int d = 0; d <= dim; ++d)
    {
        printf("%2d: [%d:%d]\n", d, svLeft(h, d), svRight(h, d));
    }

    int* p = (int*) svGetArrElemPtr(h, 1, 2, 3, 4);
    printf("%d\n", *p);
    printf("\n");
}

void dpi_func_0d(svOpenArrayHandle h)
{
    sv::openarray<sv_int,0> oa(h);
    printf("dimensions: %d\n", oa.dimensions());
    printf("      size: %d\n", oa.size());
    printf("      left: %d\n", oa.left());
    printf("     right: %d\n", oa.right());
    // printf("      left3: %d\n", oa.left(3));
    // printf("     right3: %d\n", oa.right(3));
    printf("       low: %d\n", oa.low());
    printf("      high: %d\n", oa.high());
    printf(" type left: %d\n", oa.type_left());
    printf("type right: %d\n", oa.type_right());
    for (int i = oa.low(); i <= oa.high(); ++i)
    {
        printf("%d ", oa[i]);
    }
    printf("\n\n");
}

void dpi_func_1d(svOpenArrayHandle h)
{
     sv::openarray<sv_int,1> oa(h);
    printf("    data(): %p\n", oa.data());
    printf("dimensions: %d\n", oa.dimensions());
    printf("      size: %d\n", oa.size());
    printf("      left: %d\n", oa.left());
    printf("     right: %d\n", oa.right());
    printf("       low: %d\n", oa.low());
    printf("      high: %d\n", oa.high());
    printf(" type left: %d\n", oa.type_left());
    printf("type right: %d\n", oa.type_right());
    const int* a = oa.data();
    printf("%2d\n", *(a + 0));
    printf("%2d\n", *(a + 1));
    printf("\n");

    for (int i = oa.low() - 1; i <= oa.high() + 1; ++i)
    {
        printf("%2d ", oa[i]);
        oa[i] = i * 2;
    }
    printf("\n\n");

    for (int i = oa.low(); i <= oa.high(); ++i)
    {
        printf("%2d ", oa[i]);
    }
    printf("\n\n");
}

void dpi_func_2d(svOpenArrayHandle h)
{
    sv::openarray<sv_int,2> oa(h);
    printf("dimensions: %d\n", oa.dimensions());
    printf("      size: %d\n", oa.size());
    printf("      left: %d\n", oa.left());
    printf("     right: %d\n", oa.right());
    printf("       low: %d\n", oa.low());
    printf("      high: %d\n", oa.high());
    printf(" type left: %d\n", oa.type_left());
    printf("type right: %d\n", oa.type_right());
    for (int i = oa.low() - 1; i <= oa.high() + 1; ++i)
    {
        for (int j = oa[i].low(); j <= oa[i].high(); ++j)
        {
            printf("%2d ", oa[i][j]);
            oa[i][j] *= 2;
        }
        printf("\n");
    }
    printf("\n");

    for (int i = oa.low(); i <= oa.high(); ++i)
    {
        for (int j = oa[i].low(); j <= oa[i].high(); ++j)
        {
            printf("%2d ", oa[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(/*int argc, char* argv[]*/)
{
    svOpenArrayHandle h4 = create(4, 31, 0, 1, 1, 2, 0, 2, 3, 0, 4);
    int size = 0;

    int* arr4 = alloc_arr<int>(h4, size);
    for (int i = 0; i < size; ++i)
    {
        arr4[i] = size - i;
    }

    svOpenArrayHandle h0 = create(0, 31, 0);
    int* arr0 = alloc_arr<int>(h0, size);

    svOpenArrayHandle h1 = create(1, 31, 0, 3, 2);
    int* arr1 = alloc_arr<int>(h1, size);
    for (int i = 0; i < size; ++i)
    {
        arr1[i] = i + 3;
    }

    svOpenArrayHandle h2 = create(2, 31, 0, 3, 2, 1, 3);
    int* arr2 = alloc_arr<int>(h2, size);
    for (int i = 0; i < size; ++i)
    {
        arr2[i] = i + 3;
    }

    try
    {
        dpi_func_4d(h4);
        dpi_func_0d(h0);
        dpi_func_2d(h2);
        dpi_func_1d(h1);
    }
    catch (const std::string& message)
    {
        printf("%s\n", message.c_str());
    }

    delete[] arr2;
    delete[] (unsigned char*) h2;
    delete[] arr1;
    delete[] (unsigned char*) h1;
    delete[] arr0;
    delete[] (unsigned char*) h0;
    delete[] arr4;
    delete[] (unsigned char*) h4;

    return 0;
}

// int main(/*int argc, char *argv[]*/)
// {
//     svBit b(sv_1, sv::check_throw);
//     svLogic l(sv_x, sv::check_throw);
//     cout << b << "\n";
//     cout << l << "\n";
//     cout << sv_0 << "\n";
//     cout << sv_1 << "\n";
//     cout << sv_z << "\n";
//     cout << sv_x << "\n";
//     return 0;
// }