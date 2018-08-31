/*************************************************************
* Source File:
*    Velocity : a class representing the flying object's velocity
* Author: Jotham Yelle
* Description:
*    This contains everything we need to know about the velocity class
*************************************************************/
#include "velocity.h"

/*****************************************
* Velocity
* Description: default constructor that
* starts velocity at zero
******************************************/
Velocity::Velocity()
{
	this->dx = 0.0;
	this->dy = 0.0;
}

/*****************************************
* Velocity(float. float)
* Description: non-default constructor that
* gives velocity value.  Takes two floats as
* input
******************************************/
Velocity::Velocity(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}

/*****************************************
* getDx
* Description: returns the velocity for the
* horizontal directions
******************************************/
float Velocity::getDx()
{
	return this->dx;
}

/*****************************************
* getDy
* Description: returns the velocity for the
* vertical directions
******************************************/
float Velocity::getDy()
{
	return this->dy;
}

/*****************************************
* setDx
* Description: sets the velocity for the
* horizontal directions. Takes a float as input.
******************************************/
void Velocity::setDx(float dx)
{
	this->dx += dx;
}

/*****************************************
* setDy
* Description: sets the velocity for the
* vertical directions. Takes a float as input.
******************************************/
void Velocity::setDy(float dy)
{
	this->dy += dy;
}
