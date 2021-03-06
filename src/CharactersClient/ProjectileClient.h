//
// Created by IgVelasco on 6/18/19.
//

#ifndef MARVEL_VS_CAPCOM_PROJECTILECLIENT_H
#define MARVEL_VS_CAPCOM_PROJECTILECLIENT_H


#include <SDL2/SDL_render.h>
#include "../data_structs.h"
#include "../Texture/Texture.h"
#include "../tools/ImageLoader/ImageLoader.h"

class ProjectileClient {
public:
    ProjectileClient(bool secondaryColor);

    ProjectileClient();

    void update(bool activate, character_updater_t *updater);
    virtual void render(SDL_Renderer *mRenderer, int camX, int camY);
    void load(SDL_Renderer *renderer, bool isLookingLeft);

    ImageLoader *loader;

    bool active;
    int posX;
    int posY;
    int currentSprite;
    Texture m_Texture;
    string projectileFilePath;
    string mvcFilePath;
};


#endif //MARVEL_VS_CAPCOM_PROJECTILECLIENT_H
