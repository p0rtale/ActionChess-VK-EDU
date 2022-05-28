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

        board[20] = new Knight(20, 'w', 2);
        board[21] = new Knight(21, 'w', 7);

        board[22] = new Knight(23, 'b', 2);
        board[23] = new Knight(23, 'b', 7);

        board[24] = new Bishop(24, 'w', 3);
        board[25] = new Bishop(25, 'w', 6);

        board[26] = new Bishop(26, 'b', 3);
        board[27] = new Bishop(27, 'b', 6);

        board[28] = new Queen(28, 'w', 4);
        board[29] = new Queen(29, 'b', 4);

        board[30] = new King(30, 'w', 5);
        board[31] = new King(31, 'b', 5);

        moveFigure(0, Tile(1, 4));
               moveFigure(26, Tile(1, 6));
        moveFigure(9, Tile(2, 6));
        sleep(8);
        moveFigure(0, Tile(1, 5));
        moveFigure(23, Tile(6, 6));
        moveFigure(26, Tile(1, 6));
        sleep(10);
        moveFigure(26, Tile(5, 2));
        moveFigure(16, Tile(1, 7));
        moveFigure(13, Tile(6, 5));
        moveFigure(0, Tile(2, 6));
        sleep(10);
        moveFigure(16, Tile(1, 7));
        moveFigure(0, Tile(3, 7));
        moveFigure(23, Tile(8, 5));
        sleep(2);
        moveFigure(28, Tile(5, 2));
        sleep(15);
        moveFigure(18, Tile(1,7));
        moveFigure(28, Tile(5, 7));
        moveFigure(25, Tile(3, 4));
        sleep(8);
        moveFigure(18, Tile(3,7));
        moveFigure(31, Tile(5, 7));
        sleep(15);
        moveFigure(31, Tile(5, 6));
        sleep(10);
        moveFigure(25, Tile(5, 6));
        sleep(10);
        std::cout<<this->getWinner()<<std::endl;
    }


    void FigureHandler::moveFigure(int figure, Tile endTile)
    {
        if (getWinner() != 'n')
            return;
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
                setTimer(temp, length);
            }
            else
                std::cout<<"Wrong"<<std::endl;
    }

    char FigureHandler::getWinner()
    {
        return this->winner;
    }

    void FigureHandler::setWinner(char w)
    {
        this->winner = w;
    }
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
                    {
                        if (victim->getType() == KING)
                            setWinner(figure->getColor());
                        victim->die();
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