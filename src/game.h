#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>

class SnakeGame {
public:
    SnakeGame(int width, int height);
    void run();

private:
    void draw();
    void input();
    void logic();

    int width, height, score;
    int x, y, foodX, foodY;
    int dirX, dirY;
    bool gameOver;
    std::vector<std::pair<int, int>> snake;

    void placeFood();
};

#endif