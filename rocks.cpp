#include "rocks.h"
#include "uiDraw.h"

#include <cmath>

#define M_PI 3.14159265358979323846
#define ROCK_SPEED 1

Rock::Rock()
{
	this->setAngle(random(0,360));
	this->setRotation(angle);
	this->setAlive(true);
}

BigRock::BigRock()
{
	this->setRadius(BIG_ROCK_SIZE);
	this->setSize("big");
	this->point.setX(random(random(-200, -150), random(150, 200)));
	this->point.setY(random(random(-200, -150), random(150, 200)));
}

void BigRock::draw()
{
	drawLargeAsteroid(this->point, this->getRotation());
}

void BigRock::advance()
{
	this->point.setX(this->point.getX() + (ROCK_SPEED * (-cos(M_PI / 180.0 * this->angle))));
	this->point.setY(this->point.getY() + (ROCK_SPEED * (sin(M_PI / 180.0 * this->angle))));
	this->setRotation(this->getRotation() + BIG_ROCK_SPIN);
}

void BigRock::hit()
{
	this->kill();
}

MediumRock::MediumRock()
{
	this->setAlive(true);
	this->setRadius(MEDIUM_ROCK_SIZE);
	this->setSize("medium");
}

void MediumRock::draw()
{
	drawMediumAsteroid(this->getPoint(), this->getRotation());
}

void MediumRock::advance()
{
	if (this->getFirst()) 
	{
		this->point.setY(this->point.getY() + this->velocity.getDy() + 1);

		this->point.setX(this->point.getX() + (ROCK_SPEED * (-cos(M_PI / 180.0 * this->angle))));
		this->point.setY(this->point.getY() + (ROCK_SPEED * (sin(M_PI / 180.0 * this->angle))));
		this->setRotation(this->getRotation() + MEDIUM_ROCK_SPIN);
	}
	else
	{
		this->point.setY(this->point.getY() + this->velocity.getDy() - 1);

		this->point.setX(this->point.getX() + (ROCK_SPEED * (-cos(M_PI / 180.0 * this->angle))));
		this->point.setY(this->point.getY() + (ROCK_SPEED * (sin(M_PI / 180.0 * this->angle))));
		this->setRotation(this->getRotation() + MEDIUM_ROCK_SPIN);
	}
}

void MediumRock::hit()
{
	this->kill();
}

SmallRock::SmallRock()
{
	this->setSize("small");
}

void SmallRock::draw()
{
	drawSmallAsteroid(this->point, this->getRotation());
}

void SmallRock::advance()
{
	this->point.setX(this->point.getX() + this->velocity.getDx() + this->getNewSpeed());
	this->point.setX(this->point.getX() + (ROCK_SPEED * (-cos(M_PI / 180.0 * this->angle))));
	this->point.setY(this->point.getY() + (ROCK_SPEED * (sin(M_PI / 180.0 * this->angle))));
	this->setRotation(this->getRotation() + SMALL_ROCK_SPIN);
}

void SmallRock::hit()
{
	this->kill();
}
