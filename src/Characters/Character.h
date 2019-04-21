/*
 * Character.h
 *
 *  Created on: 2 abr. 2019
 *      Author: sebastian
 */

#ifndef CHARACTERS_CHARACTER_H_
#define CHARACTERS_CHARACTER_H_

#include <SDL2/SDL_events.h>
#include "../Texture/Texture.h"
#include "../InputTable.h"
#include "../InputManager.h"
#include "../tools/ImageLoader/ImageLoader.h"
#include "../Controls/Controls.h"
#include "../tools/logger/Logger.h"

using namespace std;

class Character {
public:
    virtual~Character();
	//Maximum axis velocity of the character
	static const int CHARACTER_VEL = 10;
	virtual void load(SDL_Renderer* renderer) = 0;
	//Takes key presses and adjusts the character's velocity
//	void handleEvent(SDL_Event &e, SDL_Renderer* renderer, int distance);
	//Shows the character on the screen
	void render(SDL_Renderer* mRenderer, int camX, int camY, int posContrincante,Logger* logger);
	int getPosX();
	int getPosY();
	int getWidth();
	int getSobrante();
	int getCentro();
	void update(SDL_Renderer* renderer, int distance, int posContrincante,Logger* logger);
    void positionUpdate(int* x);
    void setControls(Controls* controls);
    void startIntro();
    bool isMakingIntro;
	bool isJumpingVertical;
	bool isJumpingRight;
	bool isJumpingLeft;
    Controls* getControls();
   	bool isMoving();
   	void setZIndex(int z);
   	int getZIndex();
   	void setFilepath(string fp);

protected:
	Character(
		int mPosX,
		int mPosY,
		int width,
		int sobrante,
		bool isLookingLeft,
		int widthSprite,
		int heightSprite,
		int anchoPantalla
	);

    //The X and Y offsets of the character
	int mPosX, mPosY;
	//The velocity of the character
	int mVelX, mVelY;

	int width, sobrante;

	int widthSprite, heightSprite;

	int INITIAL_POS_Y;

	int ZIndex;

	int anchoPantalla;

	string characterFilepath;

	Texture m_Texture;
	ImageLoader* loader;

	int currentWalkingLeftSprite;
	int currentStandingSprite;
	int currentWalkingRightSprite;
	int currentJumpingSprite;
	int currentJumpingRightSprite;
	int currentJumpingLeftSprite;
	int currentWalkbackLeftSprite;
	int currentWalkbackRightSprite;
	int currentIntroSprite;
	bool isLookingLeft;
	bool isStanding;
	bool agachado;
    Controls* characterControls;

	unsigned int lastTime;

private:
	virtual void resetSpriteVariables() = 0;
	virtual void renderStandSprite(SDL_Renderer *renderer) = 0;
	virtual void loadStandSprite(SDL_Renderer *renderer, char position) = 0;
	virtual void renderDuckSprite(SDL_Renderer *renderer) = 0;
	virtual void moveRight(SDL_Renderer *renderer, int distance, int posContrincante) = 0;
	virtual void moveLeft(SDL_Renderer *renderer, int distance, int posContrincante) = 0;
	virtual void jump(SDL_Renderer *renderer) = 0;
	virtual void jumpRight(SDL_Renderer *renderer) = 0;
	virtual void jumpLeft(SDL_Renderer *renderer) = 0;
	virtual void updateStand() = 0;
	virtual void makeIntro(SDL_Renderer* renderer) = 0;
};

#endif /* CHARACTERS_CHARACTER_H_ */
