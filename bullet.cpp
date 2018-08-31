/*************************************************************
* Source File:
*    Bullet : a class representing bullets
* Author: Jotham Yelle
* Description:
*    This contains everything we need to know about the bullet class
*************************************************************/

#include "bullet.h"
#include "uiDraw.h"

#include <cmath>

#define M_PI 3.14159265358979323846

/*****************************************
* Bullet
* Description: default constructor that
* gives the bullet a default angle
******************************************/
Bullet::Bullet()
{
	this->frames = 0;
	this->angle = 0.0;
}

/*****************************************
* advance
* Description: advances the bullet
******************************************/
void Bullet::advance()
{
	this->point.setX(this->point.getX() + this->velocity.getDx());
	this->point.setY(this->point.getY() + this->velocity.getDy());
	this->point.setX(this->point.getX() + (BULLET_SPEED * (cos(M_PI / 180.0 * this->angle))));
	this->point.setY(this->point.getY() + (BULLET_SPEED * (sin(M_PI / 180.0 * this->angle))));
	this->setFrames(this->getFrames() + 1);
	drawLanderFlames(this->getPoint(),true, false, false);
}

/*****************************************
* draw
* Description: draws the bullet on the screen
******************************************/
void Bullet::draw()
{
	drawDot(this->getPoint());
}

/*****************************************
* fire
* Description: fires the bullet
******************************************/
void Bullet::fire(Point p, float a, Velocity v)
{
	this->angle = a;
	this->point.setX(p.getX());
	this->point.setY(p.getY());
	this->velocity.setDx(v.getDx());
	this->velocity.setDy(v.getDy());
}
