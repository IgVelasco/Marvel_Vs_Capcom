
// Created by IgVelasco on 5/17/19.
//
//
#ifndef MARVEL_VS_CAPCOM_WOLVERINESERVER_H
#define MARVEL_VS_CAPCOM_WOLVERINESERVER_H

#include "./CharacterServer.h"

class WolverineServer final : public CharacterServer {
public:
    WolverineServer(int PosX, bool secondaryColor, int width, int height, int sobrante, int ancho, int anchoPantalla, int numberOfClient);
    void makeBuilderStruct(character_builder_t *builder, bool firstTeam);

private:
    void moveRight(int distance, int posContrincante);
    void moveLeft(int distance, int posContrincante);
    void resetSpriteVariables();

    int getSpriteNumber();
};

#endif //MARVEL_VS_CAPCOM_WOLVERINESERVER_H
