/*
 * InputManager.cpp
 *
 *  Created on: 2 abr. 2019
 *      Author: sebastian
 */

#include "InputManager.h"
#include <iostream>
#include <SDL2/SDL.h>

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() {
	this->quit = false;
	this->windowIsClosing = false;
	this->keyboard = SDL_GetKeyboardState(nullptr);

	for(int i = 0; i < KEYBOARD_SIZE; i++){
		this->keyStatus[i] = 0;
		this->keyHold[i] = 0;
	}
}

InputManager* InputManager::getInstance() {
	if(!instance) {
		instance = new InputManager();
	}

	return instance;
}

void InputManager::update() {

	SDL_Event event;
	while(SDL_PollEvent(&event)) {

		switch (event.type) {
		/*case SDL_QUIT:
			this->quit = true;
			break;*/

		case SDL_WINDOWEVENT:
			if(event.window.event==SDL_WINDOWEVENT_CLOSE)
			{
				std::cout<<"Se cerro la ventana "<<std::endl;
				this->windowIsClosing = true;
			}
			break;

		case SDL_KEYDOWN:

			if(event.key.repeat)
				this->keyHold[SDL_GetScancodeFromKey(event.key.keysym.sym)] = 1;

			this->keyStatus[SDL_GetScancodeFromKey(event.key.keysym.sym)] = 1;
			break;

		case SDL_KEYUP:

			this->keyStatus[SDL_GetScancodeFromKey(event.key.keysym.sym)] = 0;
			this->keyHold[SDL_GetScancodeFromKey(event.key.keysym.sym)] = 0;
			break;

		default:
			break;
		}
	}
}

bool InputManager::isKeyDown(int key) {
	if(key < 0 || key >= KEYBOARD_SIZE)
		return false;

	return this->keyStatus[key];
}

bool InputManager::isKeyUp(int key) {
	if(key < 0 || key >= KEYBOARD_SIZE)
		return false;

	return this->keyStatus[key];
}

bool InputManager::isHoldingKey(int key){
	return this->keyHold[key];
}

bool InputManager::isKeyPressed(KeyboardKey key) {
	if(!(this->keyboard))
		return false;

	int sdlKey = static_cast<int>(key);

	if(this->keyboard[sdlKey])
		return true;

	return false;
}


bool InputManager::closeWindowRequested()
{
	return this->windowIsClosing;
}

 void InputManager::windowNotClosing()
{
	this->windowIsClosing = false;
}

 bool InputManager::quitRequested()
 {
	 return this->quit;
 }

 /*
 bool InputManager::windowHasClosed()
 {
	 return this->windowClosed;
 }

 void InputManager::windowHasntClosed()
 {
	 this->windowClosed = false;
 }*/
