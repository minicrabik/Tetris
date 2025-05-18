#pragma once

#include "Grid.h"
#include "blocks.cpp"

class Game {
    private:
    Block GetRandomBlock();
    std::vector<Block>GetAllBlocks();
    std::vector<Block> blocks;
    Grid grid;
    Block currentBlock;
    Block nextBlock;
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    bool BlockFits();
    void RotateBlock();
    void LockBlock();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Sound rotateSound;
    Sound clearSound;

    public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;
    Music music;
};