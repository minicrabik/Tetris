#pragma once
#include <vector>
#include <raylib.h>

class Grid{
    private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector <Color> colors;

    public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOutside(int row, int column);
    int grid[20][10];
};