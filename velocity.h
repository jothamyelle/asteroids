/*************************************************************
* File: velocity.h
* Author: Jotham Yelle
* Description: Contains the definition of the velocity class.
*************************************************************/
#ifndef VELOCITY_H
#define VELOCITY_H

#include "velocity.h"

/*****************************************
* VELOCITY
* The velocity class containing the velocity info
*****************************************/
class Velocity
{
private:
	float dx;
	float dy;
public:
	Velocity();
	Velocity(float, float);
	float getDx();
	float getDy();
	void setDx(float);
	void setDy(float);
};


#endif // !VELOCITY_H

