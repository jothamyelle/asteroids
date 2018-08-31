#ifndef rocks_h
#define rocks_h
#include "flyingObject.h"
#include "uiDraw.h"

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10


/*****************************************
* Rock
* The Rock class containing the info
* concerning the three rocks.
*****************************************/
class Rock : public FlyingObject
{
private:
	float radius;
	std::string size;
	bool first;
	int newSpeed;
public:
	Rock();
	virtual void hit() = 0;
	void changePoint(float x, float y) {
		this->point.setX(x);
		this->point.setY(y);
	}
	float getRadius() { return this->radius; }
	void setRadius(float r) { this->radius = r; }
	float getFirst() { return this->first; }
	void setFirst(bool b) { this->first = b; }
	int getNewSpeed() { return this->newSpeed; }
	void setNewSpeed(int b) { this->newSpeed = b; }
	std::string getSize() { return this->size; }
	void setSize(std::string s) { this->size = s; }
};

/*****************************************
* BigRock
* The BigRock class containing the info
* concerning the big rocks.
*****************************************/
class BigRock : public Rock
{
public:
	BigRock();
	virtual void draw();
	virtual void advance();
	virtual void hit();
};

/*****************************************
* MediumRock
* The MediumRock class containing the info
* concerning the medium rocks.
*****************************************/
class MediumRock : public Rock
{
private:
	int mediumDirection;
public:
	MediumRock();
	virtual void draw();
	virtual void advance();
	virtual void hit();
};

/*****************************************
* SmallRock
* The SmallRock class containing the info
* concerning the small rocks.
*****************************************/
class SmallRock : public Rock
{
public:
	SmallRock();
	virtual void draw();
	virtual void advance();
	virtual void hit();
};



#endif /* rocks_h */
