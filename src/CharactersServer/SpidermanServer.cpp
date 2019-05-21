//
// Created by IgVelasco on 5/17/19.
//

#include "SpidermanServer.h"
#include "CharacterServer.h"

const int LEVEL_WIDTH = 3200;
const int LEVEL_HEIGHT = 600;

const int LAST_STANDING_SPRITE = 8;
const int LAST_WALKING_SPRITE = 10;
const int LAST_JUMPING_SPRITE = 21;
const int LAST_JUMPING_RIGHT_SPRITE = 19;
const int LAST_JUMPING_LEFT_SPRITE = 19;
const int LAST_INTRO_SPRITE = 16;



SpidermanServer::SpidermanServer(int PosX, bool secondaryColor, int width, int height, int sobrante, int ancho,
                                 int anchoPantalla, int numberOfClient)
        : CharacterServer(
        PosX,
        556 - (height * 297 / 480),
        ancho,
        sobrante,
        false,
        width,
        height,
        anchoPantalla,
        numberOfClient
) {
    lastStandingSprite = LAST_STANDING_SPRITE;
    lastWalkingSprite = LAST_WALKING_SPRITE;
    lastJumpingSprite = LAST_JUMPING_SPRITE;
    lastJumpingRightSprite = LAST_JUMPING_RIGHT_SPRITE;
    lastJumpingLeftSprite = LAST_JUMPING_LEFT_SPRITE;
    lastIntroSprite = LAST_INTRO_SPRITE;
}



void SpidermanServer::moveLeft(int distance, int posContrincante) {

    currentAction = MOVINGLEFT;
    mPosX -= CHARACTER_VEL;

    /*distance va de -800 a 800 (ancho de la pantalla)*/
    if ((mPosX - CHARACTER_VEL < -SpidermanServer::getSobrante()) || (distance < (-anchoPantalla))) {
        //Move back
        mPosX += CHARACTER_VEL;
    }

    walkingSpriteUpdate();
}


void SpidermanServer::moveRight(int distance, int posContrincante) {

    currentAction = MOVINGRIGHT;

    mPosX += CHARACTER_VEL;

    if ((mPosX + CHARACTER_VEL >= (LEVEL_WIDTH - SpidermanServer::getSobrante() - SpidermanServer::getWidth())) ||
        (distance > anchoPantalla)) {
        //Move back
        mPosX -= CHARACTER_VEL;
    }

    walkingSpriteUpdate();
}

void SpidermanServer::resetSpriteVariables(){
	return;
}

void SpidermanServer::makeBuilderStruct(character_builder_t *builder, bool firstTeam) {
	//Completar
	builder->personaje = SPIDERMAN;
	builder->cliente = clientNumber;
	builder->sprite = 0;
	builder->action = STANDING;
	builder->isFirstTeam = firstTeam;

}


int SpidermanServer::getSpriteNumber(){
    int spriteNumber;
    switch (this->currentAction){
        case STANDING:
            spriteNumber = currentStandingSprite;
            break;
        case JUMPINGVERTICAL:
            spriteNumber = currentJumpingSprite;
            break;
        case JUMPINGLEFT:
            spriteNumber = currentJumpingLeftSprite;
            break;
        case JUMPINGRIGHT:
            spriteNumber = currentJumpingRightSprite;
            break;
        case MOVINGRIGHT:
        case MOVINGLEFT:
            spriteNumber = currentWalkingSprite;
            break;
        case MAKINGINTRO:
            spriteNumber = currentIntroSprite;
            break;
        default:
            spriteNumber = 0;
            break;
    }
    return spriteNumber;
}
