#pragma once

#include "grid.h"
#include "blocks.cpp"

class Game {
    private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBlockOutside();
    bool BlockFits();
    void RotateBlock();
    void LockBlock();
    

    public:
    Game();
    Grid grid;
    Block GetRandomBlock();
    std::vector<Block>GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
};