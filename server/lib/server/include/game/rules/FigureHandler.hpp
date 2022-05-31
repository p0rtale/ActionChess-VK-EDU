#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include "Figure.hpp"
#include "Rook.hpp"
#include "King.hpp"
#include "Field.hpp"

#define CHESS_COUNT 32

#define EMPTY 0
#define ALLY 1
#define ENEMY 2

#define TIMEOUT 5

class FigureHandler
{
private:
    Figure* board[CHESS_COUNT];
    char winner;
    Field* field;
    bool isCorrect(Figure* figure, char color);
    void setTimer(Figure* figure, int length, Session* ses);
    Figure* findFigure(int id);
    Figure* findByTile(Tile tile);
    // void castling(Rock rock, King king);
public:
    FigureHandler();
    int moveFigure(int figure, Tile endTile, char color,  Session* ses);
    ~FigureHandler();
    Figure* findEnemy(Tile tile, char color);
    char isColision(Figure* figure, Tile endTile);
    char getWinner();
    void setWinner(char w);
};
