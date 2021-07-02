import "DPI-C" function void dpi_func(int openarray[][][][]);

module top;

    int da[][][][]; // dynamic array
    int fa[2][1][3][4]; // fixed-size array

    initial begin
        da = new [2];
        foreach (da[i]) begin
            da[i] = new [1];
        end
        foreach (da[i,j]) begin
            da[i][j] = new [3];
        end
        foreach (da[i,j,k]) begin
            da[i][j][k] = new [4];
        end
        // populate dynamic array
        foreach (da[i,j,k,l]) begin
            da[i][j][k][l] = i + j + k + l;
        end
        // populate fixed-size array
        foreach (fa[i,j,k,l]) begin
            fa[i][j][k][l] = i + j + k + l;
        end
        dpi_func(da);
        dpi_func(fa);
    end

endmodule