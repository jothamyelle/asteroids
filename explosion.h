#ifndef explosion_h
#define explosion_h
#include "flyingObject.h"

/*****************************************
* Explosion
* The Explosion class containing the info
* concerning the explosions.
*****************************************/
class Explosion : public FlyingObject
{
private:
	int frames;
public:
	Explosion();
	void advance();
	void draw();
	int getFrames() { return this->frames; }
	void setFrames(int f) { this->frames = f; }
};




#endif /* explosion_h */
