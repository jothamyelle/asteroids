#include "ship.h"
#include <cmath>

#define M_PI 3.14159265358979323846

// Put your ship methods here

Ship::Ship()
{
	this->alive = true;
}

/*****************************************
* applyThrustLeft
* Description: propels the Ship to the right
* and adds to the velocity
******************************************/
void Ship::moveLeft()
{
	angle += ROTATE_AMOUNT;
	if (angle > 360)
		angle = 0;
}

/*****************************************
* applyThrustRight
* Description: propels the Ship to the left
* and adds to the velocity
******************************************/
void Ship::moveRight()
{
	angle -= ROTATE_AMOUNT;
	if (angle < -360)
		angle = 0;
}

/*****************************************
* applyThrust
* Description: propels the Ship forward and 
adds to the velocity
******************************************/
void Ship::applyThrust()
{
	this->point.setX(this->point.getX() + cos(M_PI / 180.0 * this->angle));
	this->point.setY(this->point.getY() + sin(M_PI / 180.0 * this->angle));
	this->velocity.setDx(0.5 * (cos(M_PI / 180.0 * this->angle)));
	this->velocity.setDy(0.5 * (sin(M_PI / 180.0 * this->angle)));
	this->setThrust(true);
}

void Ship::advance()
{
	this->point.setX(this->point.getX() + this->velocity.getDx());
	this->point.setY(this->point.getY() + this->velocity.getDy());
	this->setThrust(false);
	this->windowWrap();
}

void Ship::draw()
{
	drawShip(this->point, this->angle - 90, this->thrust);
}
