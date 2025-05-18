#include <iostream>
#include <raylib.h>
#include "game.h"
#include "color.h"
#include "records.h"
#include <fstream>
#include <vector>
#include <algorithm>

enum GameState { MENU, PLAYING, RECORDS, GAME_OVER };

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/mobograf.ttf", 64, 0, 0);
    Game game;
    GameState gameState = MENU;
    Records records;  

    while (!WindowShouldClose()) {
        if (gameState == PLAYING) {
            UpdateMusicStream(game.music);
            game.HandleInput();
            if (EventTriggered(0.3)) {
                game.MoveBlockDown();
            }

            if (game.gameOver) {
                records.Save(game.score); 
                gameState = GAME_OVER;
            }
        }

        if (gameState == MENU && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Rectangle startButton = {150, 250, 200, 60};
            Rectangle recordsButton = {150, 330, 200, 60};
            Rectangle exitButton = {150, 410, 200, 60};

            if (CheckCollisionPointRec(mousePos, startButton)) {
                gameState = PLAYING;
            }
            if (CheckCollisionPointRec(mousePos, recordsButton)) {
                gameState = RECORDS;
            }
            if (CheckCollisionPointRec(mousePos, exitButton)) {
                break;
            }
        }

        if (gameState == GAME_OVER && IsKeyPressed(KEY_ENTER)) {
            gameState = MENU;
        }

        BeginDrawing();
        ClearBackground(darkBlue);

        if (gameState == PLAYING || gameState == GAME_OVER) {
            DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
            DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

            DrawTextEx(font, "Next", {365, 175}, 38, 2, WHITE);
            DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

            if (gameState == GAME_OVER) {
                DrawTextEx(font, "Game Over", {320, 450}, 38, 2, WHITE);
            }

            game.Draw();
        }

        if (gameState == MENU) {
            DrawTextEx(font, "TETRIS", {140 - MeasureTextEx(font, "TETRIS", 64, 2).x / 2, 100}, 64, 2, WHITE);

            Rectangle startButton = {160, 250, 200, 60};
            DrawRectangleRounded(startButton, 0.3, 6, lightBlue);
            DrawTextEx(font, "Start", {210 - MeasureTextEx(font, "Start", 38, 2).x / 2, 260}, 38, 2, WHITE);

            Rectangle recordsButton = {160, 330, 200, 60};
            DrawRectangleRounded(recordsButton, 0.3, 6, lightBlue);
            DrawTextEx(font, "Records", {190 - MeasureTextEx(font, "Records", 38, 2).x / 2, 340}, 38, 2, WHITE);

            Rectangle exitButton = {160, 410, 200, 60};
            DrawRectangleRounded(exitButton, 0.3, 6, lightBlue);
            DrawTextEx(font, "Exit", {225 - MeasureTextEx(font, "Exit", 38, 2).x / 2, 420}, 38, 2, WHITE);
        }

        if (gameState == RECORDS) {
            DrawTextEx(font, "TOP SCORES", {120, 50}, 48, 2, WHITE);

            std::vector<int> scores = records.LoadTop();
            for (int i = 0; i < std::min(10, (int)scores.size()); i++) {
                std::string scoreText = std::to_string(i + 1) + ". " + std::to_string(scores[i]);
                DrawTextEx(font, scoreText.c_str(), {150.0f, 120.0f + i * 40}, 32, 2, WHITE);
            }

            Rectangle backButton = {160, 500, 200, 60};
            DrawRectangleRounded(backButton, 0.3, 6, lightBlue);
            DrawTextEx(font, "Back", {220 - MeasureTextEx(font, "Back", 38, 2).x / 2, 510}, 38, 2, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                if (CheckCollisionPointRec(mousePos, backButton)) {
                    gameState = MENU;
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
