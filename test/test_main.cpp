#include "dpi.hpp"
#include <string>
// #include <boost/test/included/unit_test.hpp>
#include <gh/systemverilog/_experimental/simulator.hpp>

namespace sv = gh::systemverilog;

int main(/*int argc, char* argv[]*/)
{
    svOpenArrayHandle h4 = sv::create(4, 31, 0, 1, 1, 2, 0, 2, 3, 0, 4);
    int size = 0;

    int* arr4 = sv::alloc_arr<int>(h4, size);
    for (int i = 0; i < size; ++i)
    {
        arr4[i] = size - i;
    }

    svOpenArrayHandle h0 = sv::create(0, 31, 0);
    int* arr0 = sv::alloc_arr<int>(h0, size);

    svOpenArrayHandle h1 = sv::create(1, 31, 0, 3, 2);
    int* arr1 = sv::alloc_arr<int>(h1, size);
    for (int i = 0; i < size; ++i)
    {
        arr1[i] = i + 3;
    }

    svOpenArrayHandle h2 = sv::create(2, 31, 0, 3, 2, 1, 3);
    int* arr2 = sv::alloc_arr<int>(h2, size);
    for (int i = 0; i < size; ++i)
    {
        arr2[i] = i + 3;
    }

    try
    {
        dpi_func_0d(h0);
        dpi_func_1d(h1);
        dpi_func_2d(h2);
        dpi_func_4d(h4);
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
