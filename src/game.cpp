#include "game.h"
#include <iostream>
#include <conio.h>  // For _kbhit() and _getch()
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // For sleep()

SnakeGame::SnakeGame(int w, int h) : width(w), height(h), score(0), gameOver(false) {
    x = width / 2;
    y = height / 2;
    dirX = 0;
    dirY = 0;
    snake.push_back({x, y});
    srand(time(0));
    placeFood();
}

void SnakeGame::placeFood() {
    foodX = rand() % width;
    foodY = rand() % height;
}

void SnakeGame::draw() {
    system("clear"); // "cls" for Windows
    for (int i = 0; i < width+2; ++i) std::cout << "#";
    std::cout << "\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j == 0) std::cout << "#";

            if (i == y && j == x)
                std::cout << "O"; // Snake head
            else if (i == foodY && j == foodX)
                std::cout << "F";
            else {
                bool printed = false;
                for (auto s : snake) {
                    if (s.first == j && s.second == i) {
                        std::cout << "o";
                        printed = true;
                        break;
                    }
                }
                if (!printed) std::cout << " ";
            }

            if (j == width - 1) std::cout << "#";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < width+2; ++i) std::cout << "#";
    std::cout << "\nScore: " << score << "\n";
}

void SnakeGame::input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': dirX = 0; dirY = -1; break;
            case 's': dirX = 0; dirY = 1; break;
            case 'a': dirX = -1; dirY = 0; break;
            case 'd': dirX = 1; dirY = 0; break;
            case 'x': gameOver = true; break;
        }
    }
}

void SnakeGame::logic() {
    x += dirX;
    y += dirY;
    snake.insert(snake.begin(), {x, y});

    if (x == foodX && y == foodY) {
        score += 10;
        placeFood();
    } else {
        snake.pop_back(); // move forward
    }

    if (x < 0 || x >= width || y < 0 || y >= height) gameOver = true;
    for (int i = 1; i < snake.size(); ++i)
        if (snake[i] == std::make_pair(x, y))
            gameOver = true;
}

void SnakeGame::run() {
    while (!gameOver) {
        draw();
        input();
        logic();
        usleep(100000); // 100 ms
    }
    std::cout << "Game Over!\n";
}