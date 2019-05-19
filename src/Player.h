//
// Created by amaherok on 4/6/19.
//

#ifndef MARVEL_VS_CAPCOM_PLAYER_H
#define MARVEL_VS_CAPCOM_PLAYER_H


#include "CharactersClient/CharacterClient.h"
#include "Controls/Controls.h"
#include "tools/logger/Logger.h"
#include "data_structs.h"

class Player: public Renderizable {
public:
    Player(CharacterClient *first, CharacterClient *second);
    ~Player();
    void update(character_updater_t* updater);
    void render(SDL_Renderer* mRenderer, int camX, int camY, int posContrincante);
    void free();


    void loads(SDL_Renderer *pRenderer, int posContrincante);

    int getPosX();

    CharacterClient* getCurrentCharacter();

    int getWidth();

    int getSobrante();

    int getCentro();
    int getZIndex();

private:
    CharacterClient* currentCharacter;
    CharacterClient* firstCharacter;
    CharacterClient* secondCharacter;
    Controls* controls;
    int changeKey;
    bool isChanging;

    void changeCharacter();
    void setCharacterToChanging();

};


#endif //MARVEL_VS_CAPCOM_PLAYER_H
