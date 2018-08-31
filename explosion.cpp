/*************************************************************
* Source File:
*    Explosion : a class representing explosions
* Author: Jotham Yelle
* Description:
*    This contains everything we need to know about the explosion 
*    class
*************************************************************/

#include "explosion.h"
#include "uiDraw.h"

/*****************************************
* Explosion
* Description: default constructor that
* gives the Explosion a default angle
******************************************/
Explosion::Explosion()
{
	this->frames = 0;
}

/*****************************************
* advance
* Description: advances the Explosion
******************************************/
void Explosion::advance()
{
	this->setFrames(this->getFrames() + 1);
}

/*****************************************
* draw
* Description: draws the bullet on the screen
******************************************/
void Explosion::draw()
{
	drawExplosion(this->getPoint());
}