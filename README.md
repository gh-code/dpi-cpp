# DPI-C++

*WARNING: Just starting development*

 - Access open array just like normal array in C++
 - Pick svGetArrElemPtr1, svGetArrElemPtr2, ... automatically
 - Open array is typed for function overload
 - C++11

```verilog
import "DPI-C" void function dpi_func(int oa[][]);

module top;
    int arr[][];
    initial begin
        // create dynamic array
        arr = new[3];
        foreach (arr[i]) begin
            arr[i] = new[2];
        end

        // populate array
        foreach (arr[i,j]) begin
            arr[i][j] = i + j;
        end

        // pass to import DPI function
        dpi_func(arr);

        // read
        foreach (arr[i,j]) begin
            $display("%0d", arr[i][j]);
        end
    end
endmodule
```

Old way,
```cpp
void dpi_func(svOpenArrayHandle h)
{
    int i;
    int j;

    // read
    for (i = svLow(h, 1); i <= svHigh(h, 1); ++i) {
        for (j = svLow(h, 2); j <= svHigh(h, 2); ++j) {
            int* ptr = (int*) svGetArrElemPtr2(h, i, j);
            if (ptr) {
                printf("%d ", *ptr);
            }
        }
        printf("\n");
    }

    // write
    for (i = svLow(h, 1); i <= svHigh(h, 1); ++i) {
        for (j = svLow(h, 2); j <= svHigh(h, 2); ++j) {
            int* ptr = (int*) svGetArrElemPtr2(h, i, j);
            if (ptr) {
                (*ptr) *= 2;
            }
        }
    }
}
```

New way,
```cpp
namespace sv = gh::systemverilog::dpi;
using sv_int = gh::systemverilog::int_t;

void dpi_func(svOpenArrayHandle h)
{
    sv::openarray<sv_int,2> oa(h);

    // read
    for (int i = oa.low(); i <= oa.high(); ++i) {
        for (int j = oa[i].low(); j <= oa[i].high(); ++j) {
            std::cout << oa[i][j] << ' ';
        }
        std::cout << '\n';
    }

    // write
    for (int i = oa.low(); i <= oa.high(); ++i) {
        for (int j = oa[i].low(); j <= oa[i].high(); ++j) {
            oa[i][j] *= 2;
        }
    }
}
```

or
```cpp
// namespace sv = gh::systemverilog::dpi;
// using sv_int = gh::systemverilog::int_t;
//
// void dpi_func(svOpenArrayHandle h)
// {
//     sv::openarray<sv_int,2> oa(h);
//
//     // write
//     for (int i : oa) {
//         for (int j : oa[i]) {
//             oa[i][j] *= 2;
//         }
//         std::cout << '\n';
//     }
//
//     // read
//     for (int i : oa) {
//         for (int j : oa[i]) {
//             std::cout << oa[i][j];
//         }
//         std::cout << '\n';
//     }
// }
```