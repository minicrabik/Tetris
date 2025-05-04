#pragma once
#include <vector>
#include <raylib.h>

class Grid{
    private:
    std::vector<Color> GetCellColors();
    int numRows;
    int numCols;
    int cellSize;
    std::vector <Color> colors;

    public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    int grid[20][10];
};