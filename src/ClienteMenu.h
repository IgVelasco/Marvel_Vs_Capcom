/*
 * ClienteMenu.h
 *
 *  Created on: 21 may. 2019
 *      Author: german
 */

#ifndef CLIENTEMENU_H_
#define CLIENTEMENU_H_


#include "./Texture/Texture.h"

class ClienteMenu {
public:


	ClienteMenu(int posX, int team);
    void free();

    void load(SDL_Renderer* renderer, string path);
    void render(SDL_Renderer* mRenderer, int posX);

    /*void moveRight(SDL_Renderer *renderer);
    void moveLeft(SDL_Renderer *renderer);*/



private:

    int posX, team;

    Texture m_Texture;
};


#endif /* CLIENTEMENU_H_ */
