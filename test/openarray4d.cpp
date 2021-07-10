#include <gh/systemverilog/dpi.hpp>
#include "dpi.hpp"

namespace sv = gh::systemverilog::dpi;
using sv_int = gh::systemverilog::int_t;

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