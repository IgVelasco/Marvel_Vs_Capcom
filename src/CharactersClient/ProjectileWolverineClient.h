//
// Created by donatojp on 23/06/19.
//

#ifndef MARVEL_VS_CAPCOM_PROJECTILEWOLVERINECLIENT_H
#define MARVEL_VS_CAPCOM_PROJECTILEWOLVERINECLIENT_H


#include "ProjectileClient.h"

class ProjectileWolverineClient final : public ProjectileClient {

public:
    ProjectileWolverineClient(bool secondaryColor);
    virtual void render(SDL_Renderer *mRenderer, int camX, int camY);

};

#endif //MARVEL_VS_CAPCOM_PROJECTILEWOLVERINECLIENT_H
