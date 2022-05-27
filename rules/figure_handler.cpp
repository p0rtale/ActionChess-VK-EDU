#include <iostream>
#include <string>
#include "figure_handler.h"
#include "figure.h"
// #include "rock.h"
// #include "king.h"
#include "pawn.h"

    void FigureHandler::moveFigure(int figure, Tile endTile)
    {
        bool flag = false;
        Figure* temp;
        if (!endTile.isCorrect())
            {
                std::cout<<"Error there is no tile"<<std::endl;
                return;
            }
        
        for (int i = 0; i < 2; i++)
        {
            if (board[i] != nullptr && board[i]->getId() == figure)
            {
                temp = board[i];
                flag = true;
            }
        }
        if (!flag)
        {
            std::cout<<"Error there is no such figure"<<std::endl;
            delete temp;
            return;
        }
        Tile* ran;
        ran->range(temp->getPosition(), endTile);

        switch (temp->getType())
        {
        case 'p':
            if (((Pawn*) temp)->isMoveCorrect(*ran))
            {
                temp->setPosition(endTile);
                std::cout<<"Very good"<<std::endl;
            }
            else
                std::cout<<"Wrong"<<std::endl;
            break;
        
        default:
            break;
        }
    }
    // void castling(Rock rock, King king);
    FigureHandler::FigureHandler()
    {
        board[0] = new Pawn(1, 'w',1);
        moveFigure(1, Tile(4,1));
        moveFigure(1, Tile(4,1));
        moveFigure(1, Tile(5,1));
    }
    // ~FigureHandler()
    // char getWinner()
    // bool isCorrect(Figure figure)
    // bool setFlightTimer(Figure figure)
    // bool setCallDownTimer(Figure figure)
    // Tile findTile(int id)
    // Figure findFigure(int id)