#include <iostream>
#include <string>
#include "figure_handler.h"
#include "figure.h"
#include "rock.h"
#include "king.h"
#include "pawn.h"
#include "math.h"
#include <chrono>
#include <thread>
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include <mutex>
#include <sender.h>

std::mutex mtx;

    FigureHandler::FigureHandler()
    {
        field = new Field();
        this->winner = 'n';
        board[0] = new Pawn(0, 'w',1);
        board[1] = new Pawn(1, 'w',2);
        board[2] = new Pawn(2, 'w',3);
        board[3] = new Pawn(3, 'w',4);
        board[4] = new Pawn(4, 'w',5);
        board[5] = new Pawn(5, 'w',6);
        board[6] = new Pawn(6, 'w',7);
        board[7] = new Pawn(7, 'w',8);

        board[8] = new Rock(8, 'w', 1);
        board[9] = new Rock(9, 'w', 8);

        board[10] = new Knight(10, 'w', 2);
        board[11] = new Knight(11, 'w', 7);

        board[12] = new Bishop(12, 'w', 3);
        board[13] = new Bishop(13, 'w', 6);

        board[14] = new Queen(14, 'w', 4);
        board[15] = new King(15, 'w', 5);

        board[16] = new Pawn(16, 'b',1);
        board[17] = new Pawn(17, 'b',2);
        board[18] = new Pawn(18, 'b',3);
        board[19] = new Pawn(19, 'b',4);
        board[20] = new Pawn(20, 'b',5);
        board[21] = new Pawn(21, 'b',6);
        board[22] = new Pawn(22, 'b',7);
        board[23] = new Pawn(23, 'b',8);
        
        board[24] = new Rock(24, 'b', 1);
        board[25] = new Rock(25, 'b', 8);

        board[26] = new Knight(26, 'b', 2);
        board[27] = new Knight(27, 'b', 7);

        board[28] = new Bishop(28, 'b', 3);
        board[29] = new Bishop(29, 'b', 6);

        board[30] = new Queen(30, 'b', 4);

        board[31] = new King(31, 'b', 5);
    }


    int FigureHandler::moveFigure(int figure, Tile endTile, char color, Session* ses)
    {
        if (getWinner() != 'n')
            return -1;
        bool flag = false;
        if (!endTile.isCorrect())
            {
                std::cout<<"Error there is no tile"<<std::endl;
                return -1;
            }

        Figure* temp;
        temp = findFigure(figure);
        if (!isCorrect(temp, color))
            return -1;
        Tile* startTile;

        char tile_flag = isColision(temp, endTile);
        if (tile_flag == ALLY)
            {
                std::cout<<"Error there is another ally figure"<<std::endl;
                return -1;
            }
        else if (tile_flag == ENEMY) // this whole part just for pawn
            temp->setAtack(true);

        Tile* ran;
        ran->range(temp->getPosition(), endTile);
        int length = round(sqrt(ran->column*ran->column + ran->row*ran->row));

        bool move = false;
        switch (temp->getType())
        {
        case PAWN:
            move = ((Pawn*) temp)->isMoveCorrect(*ran, field, temp->getPosition());
            break;
        case ROCK:
            move = ((Rock*) temp)->isMoveCorrect(*ran, field, temp->getPosition());
            break;
        case KNIGHT:
            move = ((Knight*) temp)->isMoveCorrect(*ran, field, temp->getPosition());
            break;
        case BISHOP:
            move = ((Bishop*) temp)->isMoveCorrect(*ran, field, temp->getPosition());
            break;
        case QUEEN:
            move = ((Queen*) temp)->isMoveCorrect(*ran, field, temp->getPosition());
            break;
        case KING:
            move = ((King*) temp)->isMoveCorrect(*ran, field, temp->getPosition());
            break;
        default:
            break;
        }
        if (move)
            {
                int a = temp->getPosition().row;
                {
                    int b = temp->getPosition().column;
                    //std:: cout<<a<<" "<<b<<"\n";
                    field->feelCell(a,b, true);
                }
                temp->setPosition(endTile);
                //std::cout<<field->isEnpty(1, 4)<<"\n";
                field->feelCell(endTile.row, endTile.column, false);
                std::cout<<"Very good"<<std::endl;
                std::cout.flush();
                setTimer(temp, length, ses);
                return length;
            }
            else
                {
                    std::cout<<"Wrong"<<std::endl;
                    return -1;
                }
    }

    char FigureHandler::getWinner()
    {
        return this->winner;
    }

    void FigureHandler::setWinner(char w)
    {
        this->winner = w;
    }
    bool FigureHandler::isCorrect(Figure* figure, char color)
    {
        if (figure == nullptr)
        {
            std::cout<<"Error there is no figure"<<std::endl;
                return false;
        }
        if (figure->getColor() != color)
            return -1;
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

    void FigureHandler::setTimer(Figure* figure, int length, Session* ses)
    {
        figure->setInFlight();
        std::cout<< figure->getId()<<": Fly me to the moon\n ";
        
        std::cout.flush();
        std::thread timer ([figure, length, this, ses] ()
        {
            sleep(length);
            figure->endFlight();
            ses->write(Timeout_Move(figure->getId(), figure->getPosition()));
            std::cout<< figure->getId()<< ": reach ";
            figure->getPosition().print();

            if (figure->isAtack())
            {
                Figure* victim;
                victim = findEnemy(figure->getPosition(), figure->getColor());

                if (victim && (victim->getColor() != figure->getColor()))
                    {
                        if (victim->getType() == KING)
                        {
                            mtx.lock();
                                char clr = figure->getColor();
                                setWinner(clr);
                                ses->write(Game_Over(clr));
                            mtx.unlock();

                        }
                        mtx.lock();
                            victim->die();
                            ses->write(Delete_Figure(victim->getId()));
                        mtx.unlock();

                    }
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
    FigureHandler:: ~FigureHandler()
    {
        delete field;
        for (int i=0; i< CHESS_COUNT; i++)
            delete board[i];
    }