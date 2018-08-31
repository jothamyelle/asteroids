#ifndef ship_h
#define ship_h
#include "flyingObject.h"
#include "uiDraw.h"

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5



/*****************************************
* Ship
* The Ship class containing the info
* concerning the ship.
*****************************************/
class Ship : public FlyingObject
{
private:
	float radius;
	bool thrust;
public:
	Ship();
	Ship(Point p) { this->setPoint(p); }
	float getRadius() { return this->radius; }
	void moveRight();
	void moveLeft();
	void applyThrust();
	void setThrust(bool t) { this->thrust = t; }
	virtual void advance();
	virtual void draw();
};


#endif /* ship_h */
