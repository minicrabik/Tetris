#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "color.h"

class Block{
    private:
    int cellSize;
    int rotationState;
    std:: vector <Color> colors;
    
    public:
    Block();
    void Draw();
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    int id;
    std::map <int, std::vector <Position>> cells;
    int rowOffset;
    int columnOffset;

};
