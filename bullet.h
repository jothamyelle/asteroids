#ifndef bullet_h
#define bullet_h
#include "flyingObject.h"

#define BULLET_SPEED 5
#define BULLET_LIFE 40


/*****************************************
* Bullet
* The Bullet class containing the info
* concerning the bullets.
*****************************************/
class Bullet : public FlyingObject
{
private:
	float angle;
	int frames;
public:
	Bullet();
	void advance();
	void draw();
	void fire(Point, float, Velocity);
	int getFrames() { return this->frames; }
	void setFrames(int f) { this->frames = f; }
};




#endif /* bullet_h */
