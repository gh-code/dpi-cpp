#include <svdpi.h>
#include <gh/systemverilog/dpi.hpp>

namespace sv = gh::systemverilog;
using sv_int = gh::systemverilog::int_t;

extern "C" {
void dpi_func(svOpenArrayHandle h);
}

void dpi_func(svOpenArrayHandle h)
{
    sv::openarray<sv_int,4> oa(h);

    for (int i = oa.low(); i <= oa.high(); ++i)
    {
       for (int j = oa[i].low(); j <= oa[i].high(); ++j)
           for (int k = oa[i][j].low(); k <= oa[i][j].high(); ++k)
               for (int l = oa[i][j][k].low(); l <= oa[i][j][k].high(); ++l)
                   printf("%d ", oa[i][j][k][l]);
        printf("\n");
    }
}