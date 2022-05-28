#include <iostream>
#include <string>
#include "figure_handler.h"
#include "figure.h"
#include "rock.h"
// #include "king.h"
#include "pawn.h"
#include "math.h"
#include <chrono>
#include <thread>

    FigureHandler::FigureHandler()
    {
        board[0] = new Pawn(0, 'w',1);
        board[1] = new Pawn(1, 'w',2);
        board[2] = new Pawn(2, 'w',3);
        board[3] = new Pawn(3, 'w',4);
        board[4] = new Pawn(4, 'w',5);
        board[5] = new Pawn(5, 'w',6);
        board[6] = new Pawn(6, 'w',7);
        board[7] = new Pawn(7, 'w',8);

        board[8] = new Pawn(8, 'b',1);
        board[9] = new Pawn(9, 'b',2);
        board[10] = new Pawn(10, 'b',3);
        board[11] = new Pawn(11, 'b',4);
        board[12] = new Pawn(12, 'b',5);
        board[13] = new Pawn(13, 'b',6);
        board[14] = new Pawn(14, 'b',7);
        board[15] = new Pawn(15, 'b',8);
        
        board[16] = new Rock(16, 'w', 1);
        board[17] = new Rock(17, 'w', 8);

        board[18] = new Rock(18, 'b', 1);
        board[19] = new Rock(19, 'b', 8);

        moveFigure(0, Tile(1, 4));
        moveFigure(9, Tile(2, 6));
        sleep(8);
        moveFigure(0, Tile(1, 5));
        sleep(10);
        moveFigure(0, Tile(2, 6));
        sleep(10);
        moveFigure(16, Tile(1, 7));
        moveFigure(0, Tile(3, 7));
        sleep(15);
        
    }


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
        Tile* startTile;
        //startTile->copy(temp->getPosition());
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
        //startTile->range(endTile, *ran);
        int length = round(sqrt(ran->column*ran->column + ran->row*ran->row));

        bool move = false;
        switch (temp->getType())
        {
        case PAWN:
            move = ((Pawn*) temp)->isMoveCorrect(*ran);
            break;
        case ROCK:
            move = ((Rock*) temp)->isMoveCorrect(*ran);
            break;
        
        default:
            break;
        }
        if (move)
            {
                int a = temp->getPosition().row;
                {
                    int b = temp->getPosition().column;
                    std:: cout<<a<<" "<<b<<"\n";
                    field.feelCell(a,b, true);
                }
                temp->setPosition(endTile);
                std::cout<<field.isEnpty(1, 5)<<"\n";
                field.feelCell(endTile.row, endTile.column, false);
                std::cout<<"Very good"<<std::endl;
                std::cout.flush();
                setTimer(temp, length);
            }
            else
                std::cout<<"Wrong"<<std::endl;
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
        if (id >= CHESS_COUNT)
            return nullptr;
        if (!board[id])
            return nullptr;
        else
            return board[id];
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