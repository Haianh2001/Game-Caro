#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "draw.h"
#include "game.h"
using namespace std;

int main( int argc, char* args[] )
{
    Game app;

    int posX, posY;
    SDL_Event e;
    initWindow();
    startGame();
    while( !app.quit )
    {
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT ) app.quit = true;

			if(app.played || ( e.type == SDL_MOUSEBUTTONDOWN && posX>=170 && posX<=327
                     && posY>=277 && posY<=320))
            {
                app.played = true;
                if(app.restart){
                    app.init();

                }
                 if(app.winner ==-1 && app.player == 0 && e.type == SDL_MOUSEBUTTONDOWN
                    && e.button.clicks == 2)
                {
                    app.updateTouch(posX,posY);

                }

                if(app.winner!=-1 && e.type == SDL_MOUSEBUTTONDOWN && posX>=173
                   && posX<=329 &&posY>=279 && posY<=324)
                {
                        app.restart = true;
                }
            }
        }
         if (app.winner ==-1 && app.played)
         {
                app.update();
                app.render();
                app.winner = app.check5();
         }
         if(app.winner!=-1) endGame(app.winner);

          if( e.type == SDL_MOUSEMOTION){
                posX = e.button.x;
                posY = e.button.y;
			}
    }

	close();
    return 0;
}
