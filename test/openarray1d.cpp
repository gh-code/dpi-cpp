#include <gh/systemverilog/dpi.hpp>
#include "dpi.hpp"

namespace sv = gh::systemverilog;
using sv_int = gh::systemverilog::int_t;

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