/*
 * Box.h
 *
 *  Created on: 3 jun. 2019
 *      Author: german
 */

#ifndef BOX_H_
#define BOX_H_


#include <string>
#include <stdio.h>
#include <map>
#include <iostream>
#include "CharactersServer/Projectile.h"

using namespace std;

class Box {
private:
	int height;
	int width;
	float centerX;
	float centerY;

public:
	Box();
	Box(float x, float y,float width,float height);
	virtual ~Box();

    void setCenter(float x, float y);
	float getTop();
	float getBottom();
	float getLeft();
	float getRight();
	bool isColliding(Box* oponnentBox);
	bool contactoPorLadoDerecho(Box* box);
	bool contactoPorLadoIzquierdo(Box* box);
	bool contactInAxisY(Box *oponnentBox);

    bool contactOnAxisX(Box *oponnentBox);

    /*float xLeftBorder;
    float xRightBorder;
    float yTopBorder;
    float yBottomBorder;
     */

    void updateBox(int newWidth, int newHeight);

    bool isInsideParameters(float border, float rightBorder, float x);

    int getCenter();

    bool isProjectileColliding(Projectile *projectile);
};


#endif /* BOX_H_ */
