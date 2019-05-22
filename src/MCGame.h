//
// Created by amaherok on 3/26/19.
//

#ifndef MARVEL_VS_CAPCOM_MCGAME_H
#define MARVEL_VS_CAPCOM_MCGAME_H

#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "CharactersClient/SpidermanClient.h"
#include "CharactersClient/WolverineClient.h"
#include "tools/FPSManager/FPSManager.h"
#include "Texture/Texture.h"
#include "tools/logger/Logger.h"
#include "InputManager.h"
#include "Player.h"
#include "Layer.h"
#include "Parallax.h"
#include "tools/json/ConfigFileParser/ConfigFileParser.h"
#include "Client/TCPClient.h"
#include "data_structs.h"
#include "Constants.h"
#include <mutex>


using namespace std;


class MCGame {
private:
    bool isSending;
    bool m_Running;
    bool threadRunning;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Joystick* gGameController = NULL;
    Logger* logger;
    // Scene textures
    Texture frontGroundTexture;
    Texture middleGroundTexture;
    Texture backGroundTexture;
    Texture menuTexture;
    Layer* middleGround;
    Layer* backGround;
    Layer* frontGround;
    Player* players[2];
    Parallax* parallaxController;
    Controls* clientControls;
    json config;
    TCPClient* tcpClient;
    CharacterClient* characters[4];
    void loadGroundTextureByZIndex();
    Constants* constants;
    void action_update();
    int team;
    std::mutex m;


protected:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;


public:
    MCGame(json config, int ancho, int alto, TCPClient *client);
    ~MCGame(){}
    void init() { m_Running = true; }
    bool init(const char* title, int xpos, int ypos, int width, int
    height, int flags);
    void run();
    void menu();
    void render();
    void update();
    void handleEvents();
    void clean();
    SDL_Rect camera;

    CharacterClient *characterBuild(character_builder_t *builder);

    pthread_t readThread; //lee del socket la info de cada personaje (accion, posX, posY, etc)
    					  //y luego renderiza en base a esos datos

    pthread_t writeThread; //ejecuta handleEvents y manda en el socket (al server)
    						//la informacion de lo que el cliente pretende que el personaje haga
    						//(caminar,saltar,etc)

    void createReadThread();
    void createWriteThread();

    //Ahora le dejo este tipo de dato, pero
    												//despues lo cambiamos en base al tipo de
    												//dato que recibamos

    bool isNotActive();
};


#endif //MARVEL_VS_CAPCOM_MCGAME_H
