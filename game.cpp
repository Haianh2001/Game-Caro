#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "draw.h";
#include "game.h"
using namespace std;

void Game::init()
{
    restart = false;
    player = 0;
    winner = -1;
    for (int i = 0; i < numCell; i++)
    {
        for (int j = 0; j < numCell; j++)
            board[i][j] = -1;
    }
    selected[0] = -1;
    selected[1] = -1;
}

void Game::updateTouch(int posX, int posY)
{
    int x = posX/100;
    int y = posY/100;
    if(x>=0 && y>=0 && x<numCell && y<numCell)
    {
        selected[0] = x;
        selected[1] = y;
    }
}

int Game::check5()
{
    //check draw
    bool draw = true;
    for(int i = 0; i<numCell; i++)
        for(int j =0; j<numCell; j++)
            if(board[i][j] == -1)
                draw = false;
    if (draw)
        return 2;

    //ngang
    for(int i = 0; i<numCell; i++)
        if(board[i][1]!=-1 && board[i][1] == board[i][2] && board[i][1] == board[i][3]
                && board[i][0]==board[i][1]&& board[i][4]==board[i][1])
            return board[i][0];

    //doc
    for(int i = 0; i<numCell; i++)
        if(board[1][i] !=-1 && board[1][i] == board[2][i] && board[1][i] == board[3][i]
                &&board[0][i]==board[1][i]&& board[4][i]==board[1][i])
            return board[1][i];

    //cheo
    if(board[0][0] == board[1][1] &&
            board[0][0] == board[2][2] &&
            board[0][0] == board[3][3] &&
            board[0][0] == board[4][4] &&
            board[0][0] != -1)
    {
        return board[0][0];

    }
    else if(board[0][4] == board[1][3] &&
            board[0][4] == board[2][2] &&
            board[0][4] == board[3][1] &&
            board[0][4] == board[4][0] &&
            board[0][4] != -1)
    {
        return board[0][4];
    }
    return -1;
}

int Game:: minimax(int step)
{
    int score = check5();
    if(score != -1 || step == 4)
    {
        if(score == 1)
            score = 24-step-1;
        else if(score == 0)
            score = step-1-24;
        else
            score = 0;
        return score;
    }
    int turn = step%2;

    int tmp;
    if (turn == 1)
        score = -24;
    else
        score = 24;
    for(int i = 0; i<numCell; i++)
        for(int j = 0; j<numCell; j++)
            if(board[i][j] == -1){
                board[i][j] = turn;
                tmp = minimax(step+1);
                if (turn == 1){
                    if(tmp>score){
                        score = tmp;
                        if (step == 1){
                            rx = i;
                            ry = j;
                        }
                    }
                }
                else{
                    if(tmp<score){
                        score = tmp;
                        if (step == 1){
                            rx = i;
                            ry = j;
                        }
                    }
                }
                board[i][j] = -1;
            }
    return score;
}

void Game::update()
{
    if(selected[0] != -1 || player == 1)
    {
        if(player == 1)
        {
            minimax(1);
            selected[0] = rx;
            selected[1] = ry;
        }
        int x = selected[0];
        int y = selected[1];
        selected[0] = -1;
        if (board[x][y] !=-1)
            return;
        board[x][y] = player;
        player = 1-player;
    }
}
