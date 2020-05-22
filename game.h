#ifndef game_h_
#define game_h_

const int SCREEN_WIDTH  = 500;
const int SCREEN_HEIGHT = 500;
const int numCell = 5;
class Game
{
public:
    bool quit = false;
    bool restart = true;
    bool played = false;
    int player = 0;
    int winner = -1;
    int board[numCell][numCell];
    int selected[2];
    int rx,ry;

    void init();
    void updateTouch(int posX, int posY);
    void update();
    void render();
    int check5();
    int minimax(int turn);
    void computerAns();
};
#endif game_h_h;

