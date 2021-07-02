#include <gh/systemverilog/dpi.hpp>
#include "dpi.hpp"

namespace sv = gh::systemverilog;
using sv_int = gh::systemverilog::int_t;

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