//
// Created by amaherok on 3/26/19.
//

#include "Texture.h"

const string ERROR = "ERROR";
const string INFO = "INFO";
const string DEBUG = "DEBUG";

Texture::Texture() {
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    logger = Logger::getInstance();
}

Texture::~Texture() {
    //Deallocate
    free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer *mRenderer) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        this->logger->log("Unable to load image " + string(path.c_str()) + "! SDL_image Error: " + IMG_GetError() + "\n", ERROR);

        SDL_Surface *loadedSurface = IMG_Load("images/not_found.png");
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if (newTexture == NULL) {
        	this->logger->log("Unable to create texture from " + string(path.c_str()) + "! SDL Error: " + SDL_GetError() + "\n", ERROR);
        } else {
        	//Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    } else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if (newTexture == NULL) {
        	this->logger->log("Unable to create texture from " + string(path.c_str()) + "! SDL Error: " + SDL_GetError() + "\n", ERROR);
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void Texture::free() {
    //Free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}


void Texture::render(int x, int y, int renderWidth, int renderHeight, SDL_Renderer *mRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	/*Todas las imagenes son de 640x480, por lo que si se desea cambiar el tamaño,
	 * se debe mantener la relacion de aspecto (se calcula con una regla de tres)*/
	//SDL_Rect renderQuad = { x, y, 1153, 865 };
	/*Si se cambia el tamaño acá, solo hay que actuaizar dos constantes en los .h de
	 * los personajes: CHARACTER_WIDTH y SOBRANTE*/

	//SDL_Rect renderQuad = { x, y, mWidth+100, mHeight };
	SDL_Rect renderQuad = { x, y, renderWidth, renderHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( mRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}


int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

