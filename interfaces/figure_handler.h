#ifndef FIGURE_HANDLER_H
#define FIGURE_HANDLER_H
#include <iostream>
#include <string>
#include "figure.h"
#include "rock.h"
#include "king.h"

class FigureHandler
{
private:
    Figure board[16];
    char winner;
    void moveFigure(Figure figure, Tile startTile, Tile endTile);
    void castling(Rock rock, King king);
public:
    FigureHandler();
    ~FigureHandler();
    char getWinner();
    bool isCorrect(Figure figure);
    bool setFlightTimer(Figure figure);
    bool setCallDownTimer(Figure figure);
};

#endif