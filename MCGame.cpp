//
// Created by amaherok on 3/26/19.
//

#include "MCGame.h"
#include "Controls/WASDControls.h"
#include "Controls/ArrowControls.h"


using namespace std;

/*200 es el corrimiento a la izquierda desde el centro*/
//((LEVEL_WIDTH/2)-Spiderman::SOBRANTE)-(Spiderman::CHARACTER_WIDTH/2)-200;



const string ERROR = "ERROR";
const string INFO = "INFO";
const string DEBUG = "DEBUG";

const int SCREEN_FPS = 30;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
int distancia;
int distancia2;
int centerBefore,centerLater=-1000;


SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

void orderBackgroundsByZIndex(json* backgroundList);


bool MCGame::init(const char *title, int xpos, int ypos, int width, int height, int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

    	logger->log("SDL no se pudo inicializar.", ERROR);
        return false;

    } else {
    	logger->log("SDL Inicializó correctamente.", INFO);

        m_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_Window == 0) {

        	logger->log("Fallo al crear ventana.", ERROR);
            return false;

        } else {
        	logger->log("Ventana creada exitosamente.", INFO);

            m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (m_Renderer == 0) {
            	logger->log("Fallo al crear Renderer", ERROR);

                return false;
            } else {
            	logger->log("Renderer creado exitosamente.", INFO);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                	logger->log("SDL_image no pudo inicializarse.", ERROR);
                    return false;
                }

                player1->loads(m_Renderer);
                player2->loads(m_Renderer);


                loadGroundTextureByZIndex();
            }
        }
    }

    // everything inited successfully,
    return true;
}

void MCGame::loadGroundTextureByZIndex(){
	json firstBackgroundConfig =  this->config["battlefield"][0]["background"];
	json secondBackgroundConfig =  this->config["battlefield"][1]["background"];
	json thirdBackgroundConfig =  this->config["battlefield"][2]["background"];

	json backgroundsList[3] = {firstBackgroundConfig, secondBackgroundConfig, thirdBackgroundConfig};

	orderBackgroundsByZIndex(backgroundsList);  //Ordena la lista de backgrounds del config.json de menor a mayor segun z index.

	string backgroundFilepath = backgroundsList[0]["filepath"];
	string middlegroundFilepath = backgroundsList[1]["filepath"];
	string frontgroundFilepath = backgroundsList[2]["filepath"];

	backGroundTexture.loadFromFile("images/" + backgroundFilepath, m_Renderer);
	middleGroundTexture.loadFromFile("images/" + middlegroundFilepath, m_Renderer);
	frontGroundTexture.loadFromFile("images/" + frontgroundFilepath, m_Renderer);

	backGround->setZIndex(backgroundsList[0]["zindex"]);
	middleGround->setZIndex(backgroundsList[1]["zindex"]);
}



MCGame::MCGame(Logger* logger, json config){
	this->logger = logger;
	m_Window = NULL;
	m_Renderer = NULL;
	m_Running = false;
	this->config = config;

	int widthSpiderman = config["characters"][0]["width"];
	int heightSpiderman = config["characters"][0]["height"];
	int widthWolverine = config["characters"][1]["width"];
	int heightWolverine = config["characters"][1]["height"];

	int spidermanSobrante = widthSpiderman*242/640;
	int spidermanAncho= widthSpiderman*110/640;
	int wolverineSobrante = widthWolverine*278/640;
	int wolverineAncho= widthWolverine*87/640;

	int INITIAL_POS_X_PLAYER_ONE = ((LEVEL_WIDTH/2)-spidermanSobrante)-(spidermanAncho/2)-200;
	int INITIAL_POS_X_PLAYER_TWO = ((LEVEL_WIDTH/2)-wolverineSobrante)-(wolverineAncho/2)+200;

	logger->log("Creacion de personajes.", DEBUG);

	Character* character1 = new Spiderman(INITIAL_POS_X_PLAYER_ONE, false, widthSpiderman, heightSpiderman, spidermanSobrante, spidermanAncho);
    Character* character2 = new Wolverine(INITIAL_POS_X_PLAYER_ONE, false, widthWolverine, heightWolverine, wolverineSobrante, wolverineAncho);

    Character* character3 = new Wolverine(INITIAL_POS_X_PLAYER_TWO, true, widthWolverine, heightWolverine, wolverineSobrante, wolverineAncho);
    Character* character4 = new Spiderman(INITIAL_POS_X_PLAYER_TWO, true, widthSpiderman, heightSpiderman, spidermanSobrante, spidermanAncho);

    logger->log("Creacion de controles.", DEBUG);

    Controls* controlPlayer2 = new WASDControls();
    Controls* controlPlayer1 = new ArrowControls();

    logger->log("Creacion de Jugadores.", DEBUG);

    player1 = new Player(character1, character2, controlPlayer1);
    player2 = new Player(character3, character4, controlPlayer2);

    logger->log("Definicion de Fondo.", DEBUG);

    middleGround = new Layer(2400, 600, 3.33, 400);//3.33
    backGround = new Layer(1600,600,6.66667,800);//6.715

    logger->log("Creacion de Parallax.", DEBUG);

    parallaxController = new Parallax(&middleGround, &backGround, &camera, &centerBefore, &centerLater);
}

void MCGame::run() {
	m_Running = true;
	FPSManager fpsManager(SCREEN_FPS);

	logger->log("Inicio de Bucle MCGame-run.", DEBUG);

	while(m_Running) {
		fpsManager.start();

		handleEvents();
		update();
		render();

		fpsManager.stop();
	}
	logger->log("Fin de Bucle MCGame-run.", DEBUG);
}

void MCGame::render() {
	logger->log("Inicio render.", DEBUG);
	SDL_SetRenderDrawColor( m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(m_Renderer); // clear the renderer to the draw color
	backGround->render(camera.x, camera.y, m_Renderer, &backGroundTexture);
    middleGround->render(camera.x, camera.y, m_Renderer, &middleGroundTexture);
    frontGroundTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_Renderer, &camera);

    logger->log("Fin render fondo, inicio render jugadores.", DEBUG);

    player2->render(m_Renderer, camera.x, camera.y, player1->getPosX());
    player1->render(m_Renderer, camera.x, camera.y, player2->getPosX());
    SDL_RenderPresent(m_Renderer); // draw to the screen
}

void MCGame::clean() {
    //m_Texture.free();
    logger->log("Inicio limpieza MCGame.", INFO);
    delete player1;
    delete player2;
    logger->log("Borrado de jugadores finalizado.", DEBUG);    
    frontGroundTexture.free();
    middleGroundTexture.free();
    backGroundTexture.free();
    logger->log("Liberacion de variables de fondo finalizado.", DEBUG);
    delete backGround;
    delete middleGround;
    delete parallaxController;
    logger->log("Borrado de fondos finalizado.", DEBUG);
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    SDL_Quit();
    logger->log("Fin clean MCGame", DEBUG);
}

void MCGame::handleEvents() {
	InputManager* inputManager = InputManager::getInstance();
    inputManager->update();
    if(inputManager->quitRequested()) m_Running = false;
}

void MCGame::update() {

	logger->log("Reubicacion inicio.", DEBUG);
	//distancia = player1->getPosX() + (198/2) - player2->getPosX() + (157/2);
	//distancia2 = player2->getPosX() + (157/2) - player1->getPosX() + (198/2);
	if (player1->getCentro() > player2->getCentro()) {
		distancia = player1->getPosX()+player1->getSobrante()+player1->getWidth() - (player2->getPosX()+player2->getSobrante());
		distancia2 = player2->getPosX()+player2->getSobrante() - (player1->getPosX()+player1->getSobrante()+player1->getWidth());
	} else {
		distancia = player1->getPosX()+player1->getSobrante() - (player2->getPosX()+player2->getSobrante()+player2->getWidth());
		distancia2 = player2->getPosX()+player2->getSobrante()+player2->getWidth() - (player1->getPosX()+player1->getSobrante());
	}
    logger->log("Actualizacion posicion MCGame.", DEBUG);
    player1->update(m_Renderer, distancia, player2->getCentro());
    player2->update(m_Renderer, distancia2, player1->getCentro());

    logger->log("Actualizacion parallax - MCGame.", DEBUG);
    parallaxController->doParallax(&player1,&player2);
}

void orderBackgroundsByZIndex(json* backgroundList){

	int pos_sel = 0;
	json aux;

//	logger->log("Definicion de ubicacion segun zindex.", INFO);
	for(int i = 2; i >= 0; i--){

		for(int x = 0; x <= i; x++){
			if(backgroundList[x]["zindex"] > backgroundList[pos_sel]["zindex"]){
				pos_sel = x;
			}
		}

		aux = backgroundList[i];
		backgroundList[i] = backgroundList[pos_sel];
		backgroundList[pos_sel] = aux;
		pos_sel = 0;
//	logger->log("Fin definicion de ubicacion segun zindex.", INFO);
	}
}