//
// Created by IgVelasco on 6/20/19.
//

#ifndef MARVEL_VS_CAPCOM_ROUNDBANNER_H
#define MARVEL_VS_CAPCOM_ROUNDBANNER_H


#include "action_constants.h"
#include "tools/ImageLoader/ImageLoader.h"
#include "data_structs.h"

class RoundBanner {

public:
    RoundBanner();
    bool active;
    round_action_t currentAction;
    int currentWinner;
    int numberOfRound;

    void load();

    ImageLoader *loader;

    void render(SDL_Renderer *mRenderer);

    Texture m_Texture;

    void updateRoundSprites(round_info_t round);
};


#endif //MARVEL_VS_CAPCOM_ROUNDBANNER_H
