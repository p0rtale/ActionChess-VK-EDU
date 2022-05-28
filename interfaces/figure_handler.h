#ifndef FIGURE_HANDLER_H
#define FIGURE_HANDLER_H
#include <iostream>
#include <string>
#include "figure.h"
#include "rock.h"
#include "king.h"
#include <unistd.h>
#include <chrono>
#include <thread>

#define CHESS_COUNT 3

#define EMPTY 0
#define ALLY 1
#define ENEMY 2

#define TIMEOUT 5

class FigureHandler
{
private:
    Figure* board[CHESS_COUNT];
    char winner;
    bool isCorrect(Figure* figure);
    void setTimer(Figure* figure, int length);
    Figure* findFigure(int id);
    Figure* findByTile(Tile tile);
    // void castling(Rock rock, King king);
public:
    FigureHandler();
    void moveFigure(int figure, Tile endTile);
    // ~FigureHandler();
    // char getWinner();

    // Tile findTile(int id);
    Figure* findEnemy(Tile tile, char color);
    char isColision(Figure* figure, Tile endTile);
};

#endif