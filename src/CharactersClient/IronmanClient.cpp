//
// Created by IgVelasco on 6/22/19.
//

#include "IronmanClient.h"
#include "../InputTable.h"
#include "ProjectileIronmanClient.h"


const Uint8 SECONDARY_RED = 0;
const Uint8 SECONDARY_GREEN = 200;
const Uint8 SECONDARY_BLUE = 255;

const string IronManPath = "images/iron_man/iron_man_";
const string MVC_FILEPATH = "/MVC2_IronMan_";
const string FILE_EXTENSION = ".png";

IronmanClient::IronmanClient(int PosX, bool secondaryColor, int width, int height, int sobrante, int ancho,
                                 int anchoPantalla, int numOfClient)
        : CharacterClient(
        PosX,
        556 - (height * 297 / 480),
        ancho,
        sobrante,
        false,
        width,
        height,
        anchoPantalla, numOfClient) {
    this->characterFilePath = IronManPath;
    if (secondaryColor)
        loader = new ImageLoader(SECONDARY_RED, SECONDARY_GREEN, SECONDARY_BLUE);
    else
        loader = new ImageLoader((Uint8) 255, (Uint8) 255, (Uint8) 255);
    currentAction = STANDING;
    projectile = new ProjectileIronmanClient(secondaryColor);

}

IronmanClient::~IronmanClient() {
}

void IronmanClient::load(SDL_Renderer *renderer, int posContrincante) {



    isLookingLeft = this->getCentro() > posContrincante;
    switch (this->currentAction) {
        case STANDING:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "standing_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "standing_right", MVC_FILEPATH,
                                               currentSprite, FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case PUNCHINGJUMPLEFT:
        case PUNCHINGJUMPRIGHT:
        case PUNCHINGVERTICAL:
        case PUNCHINGSTRONGJUMPLEFT:
        case PUNCHINGSTRONGJUMPRIGHT:
        case PUNCHINGSTRONGVERTICAL:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "punch_air_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "punch_air_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case PUNCH:
        case PUNCHSTRONG:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "punch_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "punch_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;


        case KICKINGVERTICAL:
        case KICKINGJUMPRIGHT:
        case KICKINGJUMPLEFT:
        case KICKINGSTRONGVERTICAL:
        case KICKINGSTRONGJUMPRIGHT:
        case KICKINGSTRONGJUMPLEFT:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "kick_air_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "kick_air_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;
        case KICK:
        case KICKSTRONG:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "kick_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "kick_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case THROWPOWER:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "throw_power_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "throw_power_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case HURTINGGROUND:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "pain_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "pain_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case HURTINGAIR:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "fall_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "fall_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case PUNCHDOWN:
        case PUNCHSTRONGDOWN:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "punch_down_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "punch_down_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case KICKDOWN:
        case KICKSTRONGDOWN:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "kick_down_left", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "kick_down_right", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case DUCK:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "duck", MVC_FILEPATH, 1, FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "duck", MVC_FILEPATH, 0, FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case BLOCK:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "block", MVC_FILEPATH, 1, FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "block", MVC_FILEPATH, 0, FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;


        case THROW:
		if (isLookingLeft)
			this->loader->loadActionSprite(characterFilePath + "throw_left",
					MVC_FILEPATH, currentSprite, FILE_EXTENSION, renderer,
					&m_Texture);
		else
			this->loader->loadActionSprite(characterFilePath + "throw_right",
					MVC_FILEPATH, currentSprite, FILE_EXTENSION, renderer,
					&m_Texture);
		break;

		case GRIP:
			if (isLookingLeft)
				this->loader->loadActionSprite(characterFilePath + "grip_left",
						MVC_FILEPATH, currentSprite, FILE_EXTENSION, renderer,
						&m_Texture);
			else
				this->loader->loadActionSprite(characterFilePath + "grip_right",
						MVC_FILEPATH, currentSprite, FILE_EXTENSION, renderer,
						&m_Texture);
			break;

		case FALLING:
			if (isLookingLeft)
				this->loader->loadActionSprite(characterFilePath + "falling_left",
						MVC_FILEPATH, currentSprite, FILE_EXTENSION, renderer,
						&m_Texture);
			else
				this->loader->loadActionSprite(characterFilePath + "falling_right",
						MVC_FILEPATH, currentSprite, FILE_EXTENSION, renderer,
						&m_Texture);
			break;

        case JUMPINGVERTICAL:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "jumping_inverted", MVC_FILEPATH,
                                               currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "jumping", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;
        case JUMPINGRIGHT:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "jumping_right_inverted", MVC_FILEPATH,
                                               currentSprite, FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "jumping_right", MVC_FILEPATH,
                                               currentSprite, FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;
        case JUMPINGLEFT:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "jumping_left", MVC_FILEPATH,
                                               currentSprite, FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "jumping_left_inverted", MVC_FILEPATH,
                                               currentSprite, FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;

        case MAKINGINTRO:
        	this->loadBanner(renderer);
         	this->loader->loadActionSprite(characterFilePath + "intro", MVC_FILEPATH, currentSprite,
                                               FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;
        case MOVINGLEFT:
        case MOVINGRIGHT:
            if (isLookingLeft)
                this->loader->loadActionSprite(characterFilePath + "walking_left", MVC_FILEPATH,
                                               currentSprite, FILE_EXTENSION,
                                               renderer, &m_Texture);
            else
                this->loader->loadActionSprite(characterFilePath + "walking_right", MVC_FILEPATH,
                                               currentSprite, FILE_EXTENSION,
                                               renderer, &m_Texture);
            break;
    }
    projectile->load(renderer, isLookingLeft);
}

void IronmanClient::render(SDL_Renderer *mRenderer, int camX, int camY, int posContrincante) {
    isLookingLeft = this->getCentro() > posContrincante;
    m_Texture.render(mPosX - camX + 260, mPosY - camY + 85 + 180, widthSprite, heightSprite,
                     mRenderer);  //esto es los valores que se cambian la resolucion
}


void IronmanClient::loadBanner(SDL_Renderer *renderer)
{
	if (this->clientNumber == 0 || this->clientNumber == 1) {
			this->loader->loadActionSprite(characterFilePath + "banner_left",
					MVC_FILEPATH, 0, FILE_EXTENSION, renderer,
					&characterLeftCurrentBanner);

			this->loader->loadActionSprite(characterFilePath + "banner_left",
					MVC_FILEPATH, 1, FILE_EXTENSION, renderer,
					&characterLeftSecondaryBanner);
	} else {

		this->loader->loadActionSprite(characterFilePath + "banner_right",
				MVC_FILEPATH, 0, FILE_EXTENSION, renderer,
				&characterRightCurrentBanner);

			this->loader->loadActionSprite(characterFilePath + "banner_right",
					MVC_FILEPATH, 1, FILE_EXTENSION, renderer,
					&characterRightSecondaryBanner);
	}
}

void IronmanClient::renderVictoryPose(SDL_Renderer *mRenderer, int posX){
	victoryTexture.loadFromFile("images/pantalla_final/ironman.png", mRenderer);
	victoryTexture.render(posX, 120, 640, 480, mRenderer);
}



