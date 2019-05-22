/*
 * ClienteMenu.cpp
 *
 *  Created on: 21 may. 2019
 *      Author: german
 */


#include "ClienteMenu.h"

using namespace std;

ClienteMenu::ClienteMenu(int posX, int team) {
    this->posX = posX;
    this->team = team;
}


/*void ClienteMenu::moveLeft(SDL_Renderer *renderer) {
	posX = 97;

}


void ClienteMenu::moveRight(SDL_Renderer *renderer) {
    posX = 449;
}*/


void ClienteMenu::render(SDL_Renderer *mRenderer, int posX) {
	int posY;
	if (team == 1) posY = 61;
	else posY = 353;
    m_Texture.render(posX, posY, 254, 221, mRenderer);
}


void ClienteMenu::load(SDL_Renderer *renderer, string path) {
    m_Texture.loadFromFile(path, renderer);
}


void ClienteMenu::free() {
    m_Texture.free();
}



