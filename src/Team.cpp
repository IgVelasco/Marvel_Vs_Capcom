/*
 * Team.cpp
 *
 *  Created on: 18 may. 2019
 *      Author: caropistillo
 */

#include "Team.h"
#include "CharactersServer/SpidermanServer.h"
#include "CharactersServer/WolverineServer.h"

const int MAX_PLAYERS = 4;

Team::Team(CharacterServer* firstCharact, CharacterServer* secondCharact, int teamSize, int teamNumber )
{
	this->currentCharacter = firstCharact;  //es el que esta jugando ahora
	this->firstCharacter = firstCharact;
	this->secondCharacter = secondCharact;
	this->sizeOfTeam = teamSize;
	this->teamNumber = teamNumber;
	isChanging = false;
	clientActive = currentCharacter->clientNumber;

}

void Team::changeCharacter(Socket** sockets)
{
    sockets[currentCharacter->clientNumber]->receivingFromClient = false;
    int updateX = currentCharacter->getCentro();

    if(currentCharacter == firstCharacter) {
        currentCharacter = secondCharacter;
    }
    else {
        currentCharacter = firstCharacter;
    }
    currentCharacter->positionUpdate(&updateX);

    sockets[currentCharacter->clientNumber]->receivingFromClient = true;
    this->clientActive = currentCharacter->clientNumber;
    this->currentCharacter->currentAction = MAKINGINTRO;

}


void Team::update(int distance, int posContrincante, actions_t action, Socket** sockets, Box* boxContrincante) {

    if(action == CHANGEME && currentCharacter->currentAction == STANDING)
    {
        changeCharacter(sockets);
        isChanging = true;
    }

    if(!(currentCharacter->currentAction == MAKINGINTRO))
        isChanging = false;

    currentCharacter->update(distance, posContrincante, action, boxContrincante);
}

void Team::changeClient(){

    if(currentCharacter == firstCharacter)
        this->clientActive = secondCharacter->clientNumber;
    else
        this->clientActive = firstCharacter->clientNumber;

}

void Team::makeUpdater(character_updater_t* updater){
	updater->team = this->teamNumber;
	this->currentCharacter->makeUpdaterStruct(updater);
}

CharacterServer* Team::get_currentCharacter()
{
	return this->currentCharacter;
}

bool Team::invalidIntroAction()
{
	actions_t action = currentCharacter->currentAction;

	return ( (action == JUMPINGLEFT) || (action == JUMPINGRIGHT) || (action == JUMPINGVERTICAL)
			|| (action == DUCK) || (action == MOVINGRIGHT) || (action == MOVINGLEFT)
			|| (action == WALKBACK) || (action == PUNCH) || (action == KICK) || (action == PUNCHDOWN)
			|| (action == KICKDOWN));
}


