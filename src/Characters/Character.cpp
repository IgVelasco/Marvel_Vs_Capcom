/*
 * Character.cpp
 *
 *  Created on: 2 abr. 2019
 *      Author: sebastian
 */

#include "Character.h"
#include "../tools/logger/Logger.h"

const string ERROR = "ERROR";
const string INFO = "INFO";
const string DEBUG = "DEBUG";


// Protected
Character::Character(
        int mPosX,
        int mPosY,
		int width,
		int sobrante,
        bool isLookingLeft,
		int widthSprite,
		int heightSprite,
		int anchoPantalla
) {
    this->mPosX = mPosX;
    this->mPosY = mPosY;
    this->width = width;
    this->sobrante = sobrante;
    this->widthSprite = widthSprite;
    this->heightSprite = heightSprite;
    this->INITIAL_POS_Y= mPosY;
    this->mVelX = 0;
    this->mVelY = 0;
    this->ZIndex = 0;
    this->anchoPantalla = anchoPantalla;
    this->characterFilepath = "";
    this->currentWalkingLeftSprite = 0;
    this->currentWalkingRightSprite = 0;
    this->currentStandingSprite = 0;
    this->currentWalkbackLeftSprite = 0;
    this->currentWalkbackRightSprite = 0;
    this->currentJumpingSprite = 0;
    this->currentJumpingRightSprite = 0;
    this->currentJumpingLeftSprite = 0;
    this->currentIntroSprite = 0;
    this->isLookingLeft = isLookingLeft;
    this->isStanding = true;
    this->agachado = false;
    this->isJumpingVertical = false;
    this->isJumpingRight = false;
    this->isJumpingLeft = false;
    this->isMakingIntro = false;

    this->loader = NULL;
    this->characterControls = NULL;

    this->lastTime = SDL_GetTicks();

}

// Public:
void Character::update(SDL_Renderer *renderer, int distance, int posContrincante,Logger* logger) {

    InputManager *inputManager = InputManager::getInstance();

    if (isMakingIntro){
    	makeIntro(renderer);
    	return;
    }

    if (isJumpingVertical) {    //Si saltaba verticalmente, lo fuerzo a que siga con esa accion
        jump(renderer);
        return;
    }

    if (isJumpingRight) {        //Si saltaba hacia la derecha, lo fuerzo a que siga con esa accion

        moveRight(renderer, distance, posContrincante);
        jumpRight(renderer);
        return;
    }

    if (isJumpingLeft) {

        moveLeft(renderer, distance, posContrincante);
        jumpLeft(renderer);
        return;
    }

    //Acciones de dos teclas primero
    if (inputManager->isKeyDown(characterControls->upKey) && inputManager->isKeyDown(characterControls->rightKey)) jumpRight(renderer);
    else if (inputManager->isKeyDown(characterControls->upKey) && inputManager->isKeyDown(characterControls->leftKey)) jumpLeft(renderer);

        //Acciones de una sola tecla
    else if (inputManager->isKeyDown(characterControls->upKey)) jump(renderer);
    else if (inputManager->isKeyDown(characterControls->downKey)) renderDuckSprite(renderer);
    else if (inputManager->isKeyDown(characterControls->rightKey) && !inputManager->isKeyUp(characterControls->leftKey))
        moveRight(renderer, distance, posContrincante);
    else if (inputManager->isKeyDown(characterControls->leftKey) && !inputManager->isKeyUp(characterControls->rightKey))
        moveLeft(renderer, distance, posContrincante);


    if (
            (!inputManager->isKeyUp(characterControls->upKey) &&
             !inputManager->isKeyUp(characterControls->downKey) &&
             !inputManager->isKeyUp(characterControls->rightKey) &&
             !inputManager->isKeyUp(characterControls->leftKey))
            || (inputManager->isKeyUp(characterControls->rightKey) &&
                inputManager->isKeyUp(characterControls->leftKey))
            )
        this->renderStandSprite(renderer);

    updateStand();
}

void Character::render(SDL_Renderer *mRenderer, int camX, int camY, int posContrincante,Logger* logger) {
    if (this->getCentro() > posContrincante) {
        isLookingLeft = true;
    } else {
        isLookingLeft = false;
    }

    if (isStanding && !agachado)
        renderStandSprite(mRenderer);

    //int ancho;
    //int alto;

    /*
	if (Character::name == "Spiderman") {
		ancho = j["characters"][0]["width"];
		alto = j["characters"][0]["height"];
	} else {
		ancho = j["characters"][1]["width"];
		alto = j["characters"][1]["height"];
	}*/

    m_Texture.render(mPosX - camX, mPosY - camY, widthSprite, heightSprite, mRenderer); //esto es los valores que se cambian la resolucion
}


int Character::getPosX() {
    return mPosX;
}

int Character::getPosY() {
    return mPosY;
}

int Character::getWidth() {
    return width;
}

int Character::getSobrante() {
    return sobrante;
}

int Character::getCentro() {
    int centro;
    centro = this->getPosX()+this->getSobrante()+(this->getWidth())/2;
    return centro;
}

Character::~Character() {
    delete loader;
    m_Texture.free();
}

void Character::positionUpdate(int* x) {
	/*x tiene el centro del personaje (ubicacion exacta del personaje)
	 * La posicion en x se calcula con eso*/
    mPosX = *x - this->getSobrante() - (this->getWidth()/2);
}

void Character::setControls(Controls* controls) {
    characterControls = controls;
}

void Character::startIntro(){
	isMakingIntro = true;
}

Controls* Character::getControls()
{
	return this->characterControls;
}

bool Character::isMoving()
{
	return !(this->isStanding || this->isJumpingVertical || this->agachado || this->isMakingIntro);
}

int Character::getZIndex(){
	return this->ZIndex;
}

void Character::setZIndex(int z){
	this->ZIndex = z;
}

void Character::setFilepath(string fp){
	this->characterFilepath = fp;
}





