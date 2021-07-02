#include <gh/systemverilog/dpi.hpp>
#include "dpi.hpp"
// #include <boost/test/included/unit_test.hpp>

namespace sv = gh::systemverilog;
using sv_int = gh::systemverilog::int_t;

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