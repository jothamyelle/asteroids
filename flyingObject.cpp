/*************************************************************
* Source File:
*    Flying Objects : a class representing bullets, ships, and
*    asteroids
* Author: Jotham Yelle
* Description:
*    This contains everything we need to know about objects
*    that will be flying in our game
*************************************************************/
#include "flyingObject.h"

/*****************************************
* FlyingObject
* Description: default constructor that
* starts FlyingObject with a default point,
* velocity, and life status
******************************************/
FlyingObject::FlyingObject()
{
	this->point.setX(0);
	this->point.setY(0);
	this->alive = true;
}

FlyingObject::FlyingObject(Point p, Velocity v, bool b)
{
	this->point = p;
	this->velocity = v;
	this->alive = b;
}

/*****************************************
* kill()
* Description: deletes the flying object
******************************************/
void FlyingObject::kill()
{
	this->setAlive(false);
}

/**************************************************************************
* GAME :: WINDOWWRAP
*
* 1. If the object goes off screen, make it appear on the opposite side
**************************************************************************/
void FlyingObject::windowWrap()
{
	if (point.getX() < -200)
		point.setX(200);
	if (point.getX() > 200)
		point.setX(-200);
	if (point.getY() < -200)
		point.setY(200);
	if (point.getY() > 200)
		point.setY(-200);
}
