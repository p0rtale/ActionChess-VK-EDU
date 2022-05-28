#include <iostream>
#include <string>
#include "figure_handler.h"
#include "figure.h"
// #include "rock.h"
// #include "king.h"
#include "pawn.h"
#include "math.h"
#include <chrono>
#include <thread>



    void FigureHandler::moveFigure(int figure, Tile endTile)
    {
        bool flag = false;
        if (!endTile.isCorrect())
            {
                std::cout<<"Error there is no tile"<<std::endl;
                return;
            }

        Figure* temp;
        temp = findFigure(figure);
        if (!isCorrect(temp))
            return;
        char tile_flag = isColision(temp, endTile);
        if (tile_flag == ALLY)
            {
                std::cout<<"Error there is another ally figure"<<std::endl;
                return;
            }
        else if (tile_flag == ENEMY) // this whole part just for pawn
            temp->setAtack(true);

        Tile* ran;
        ran->range(temp->getPosition(), endTile);
        int length = round(sqrt(ran->column*ran->column + ran->row*ran->row));

        switch (temp->getType())
        {
        case 'p':
            if (((Pawn*) temp)->isMoveCorrect(*ran))
            {
                temp->setPosition(endTile);
                std::cout<<"Very good"<<std::endl;
                std::cout.flush();
                setTimer(temp, length);
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
        board[1] = new Pawn(2, 'w',2);
        board[1]->die();
        moveFigure(1, Tile(4,1));
        board[2] = new Pawn(3, 'b',2);
        moveFigure(3, Tile(6,2));
        sleep(8);
        moveFigure(1, Tile(5,1));
        sleep(10);
        moveFigure(1, Tile(6,2));

        sleep(10);
    }
    // char getWinner()
    bool FigureHandler::isCorrect(Figure* figure)
    {
        if (figure == nullptr)
        {
            std::cout<<"Error there is no figure"<<std::endl;
                return false;
        }
        if (figure->isDead())
        {
            std::cout<<"Error figure is dead"<<std::endl;
                return false;
        }
        if (figure->isOnCallDown() || figure->isInFlight())
        {
            std::cout<<"Error figure is busy"<<std::endl;
                return false;
        }
        return true;
    }

    void FigureHandler::setTimer(Figure* figure, int length)
    {
        figure->setInFlight();
        std::cout<< figure->getId()<<": Fly me to the moon\n ";
        std::cout<< figure->getId()<< ": "<<length<<std::endl;
        
        std::cout.flush();
        std::thread timer ([figure, length, this] ()
        {
            sleep(length);
            figure->endFlight();
            std::cout<< figure->getId()<< ": reach ";
            figure->getPosition().print();

            if (figure->isAtack())
            {
                Figure* victim;
                victim = findEnemy(figure->getPosition(), figure->getColor());

                if (victim && (victim->getColor() != figure->getColor()))
                    victim->die();
                figure->setAtack(false);
            }

            std::cout.flush();
            figure->setOnCallDown();
            std::cout<<"timer for " << figure->getId()<<std::endl;
            std::cout.flush();
            sleep(TIMEOUT);
            std::cout<<figure->getId()<<": SSSS\n";
            figure->endCallDown();
        });
        timer.detach();
    }

    Figure* FigureHandler::findFigure(int id)
    {
        for (int i = 0; i < CHESS_COUNT; i++)
            {
                if (board[i] && board[i]->getId() == id)
                    return board[i];
            }
        return nullptr;
    }

    Figure* FigureHandler::findByTile(Tile tile)
    {
        for (int i = 0; i < CHESS_COUNT; i++)
            {
                if (board[i] && board[i]->getPosition().isEqual(tile))
                    return board[i];
            }
        return nullptr;
    }

    char FigureHandler::isColision(Figure* figure, Tile endTile)
    {
        Figure* temp;
        temp = findByTile(endTile);
       
        if (!temp) 
            return EMPTY;
        if ((temp->getColor() == figure->getColor()) && !temp->isDead())
            return ALLY;
        if ((temp->getColor() != figure->getColor()) && !temp->isDead())
            return ENEMY;
        return EMPTY;
    }
    Figure* FigureHandler::findEnemy(Tile tile, char color)
    {
        for (int i = 0; i < CHESS_COUNT; i++)
            {
                if (board[i] && board[i]->getPosition().isEqual(tile) && board[i]->getColor() != color)
                    return board[i];
            }
        return nullptr;
    }