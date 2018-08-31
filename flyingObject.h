/*************************************************************
* File: flyingObject.h
* Author: Jotham Yelle
* Description: Contains the definition of the flyingObjects class.
*************************************************************/
#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H

#include "point.h"
#include "velocity.h"

/*****************************************
* FlyingObject
* The FlyingObject class containing the
* info concerning all flying objects
*****************************************/
class FlyingObject
{
protected:
	Point point;
	Point startingPoint;
	Velocity velocity;
	bool alive;
	float angle;
	float rotation;
public:
	FlyingObject();
	FlyingObject(Point, Velocity, bool);
	Point getPoint() { return this->point; }
	Velocity getVelocity() { return this->velocity; }
	bool isAlive() { return this->alive; }
	void setPoint(Point point) { this->point = point; }
	void setVelocity(Velocity velocity) { this->velocity = velocity; }
	void setAlive(bool b) { this->alive = b; }
	virtual void draw() = 0;
	virtual void advance() = 0;
	void setAngle(float a) { this->angle = a; }
	float getAngle() { return this->angle; }
	void kill();
	void setRotation(float r) { this->rotation = r; }
	float getRotation() { return this->rotation; }
	void windowWrap();
};


#endif // !FLYINGOBJECT_H
