/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementation of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"

#include <vector>

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5

/***************************************
* GAME CONSTRUCTOR
***************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br)
{
	// Set up the initial conditions of the game
	score = 0;
	play = false;
	for (int i = 0; i < 5; i++)
	{
		rocks.push_back(rock);
	}

	for (int i = 0; i < rocks.size(); i++)
		rocks[i] = NULL;

	for (int i = 0; i < 5; i++)
	{
		if (rocks[i] == NULL)
		{
			// there is no rock right now, possibly create one
			// create a new rock
			rocks[i] = createBigRock();
		}
	}
}

/****************************************
* GAME DESTRUCTOR
****************************************/
Game :: ~Game()
{
	// TODO: Check to see if there is currently a rock allocated
	//       and if so, delete it.
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			delete rocks[i];
			rocks[i] = NULL;
		}
	}
}

/***************************************
* GAME :: ADVANCE
* advance the game one unit of time
***************************************/
void Game::advance()
{
	advanceBullets();
	advanceExplosions();
	advanceRock();
	ship.advance();

	handleCollisions();
	cleanUpZombies();

	if (!ship.isAlive())
	{
		Point gameOver(-125, 0);
		drawText(gameOver, "Ya done messed up... better luck next time!");
	}
}

/***************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
***************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i]->advance();
			bullets[i]->windowWrap();

			if (bullets[i]->getFrames() == 40)
			{
				bullets[i]->kill();
			}
		}
	}
}

/***************************************
* GAME :: ADVANCE EXPLOSIONS
* Go through each explosion and advance it.
***************************************/
void Game::advanceExplosions()
{
	// Give life to each explosion
	for (int i = 0; i < explosions.size(); i++)
	{
		if (explosions[i]->isAlive())
		{
			// this explosion is alive, so tell it to dance
			explosions[i]->advance();

			if (explosions[i]->getFrames() == 2)
			{
				explosions[i]->kill();
			}
		}
	}
}

/**************************************************************************
* GAME :: ADVANCE ROCK
* If there is a rock, and it's alive, advance it
**************************************************************************/
void Game::advanceRock()
{
	for (int i = 0; i < rocks.size(); i++)
	{
		// we have a rock, make sure it's alive
		if (rocks[i]->isAlive())
		{
			// move it forward
			rocks[i]->advance();
			rocks[i]->windowWrap();
		}
	}

}

/**************************************************************************
* GAME :: CREATE BIG ROCK
* Create a rock of a type according to the rules of the game.
**************************************************************************/
Rock* Game::createBigRock()
{
	Rock* newRock = new BigRock;

	return newRock;
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
* GAME :: HANDLE COLLISIONS
* Check for a collision between a rock and a bullet.
**************************************************************************/
void Game::handleCollisions()
{
	for (int j = 0; j < rocks.size(); j++)
	{
		// check if the rock and ship are colliding
		if (fabs(ship.getPoint().getX() - rocks[j]->getPoint().getX()) < CLOSE_ENOUGH
			&& fabs(ship.getPoint().getY() - rocks[j]->getPoint().getY()) < CLOSE_ENOUGH)
		{
			// if they've hit, then run the hit function
			rocks[j]->hit();
			// if the rock is big
			if (rocks[j]->getSize() == "big")
			{
				// break it into two medium rocks
				Rock * newMediumRock1 = new MediumRock;
				newMediumRock1->changePoint(rocks[j]->getPoint().getX(), rocks[j]->getPoint().getY() + 32);
				newMediumRock1->setVelocity(rocks[j]->getVelocity());
				newMediumRock1->setAngle(rocks[j]->getAngle());
				newMediumRock1->setFirst(true);
				rocks.push_back(newMediumRock1);
				Rock * newMediumRock2 = new MediumRock;
				newMediumRock2->changePoint(rocks[j]->getPoint().getX(), rocks[j]->getPoint().getY() - 32);
				newMediumRock2->setVelocity(rocks[j]->getVelocity());
				newMediumRock2->setAngle(rocks[j]->getAngle());
				newMediumRock2->setFirst(false);
				rocks.push_back(newMediumRock2);
				// and one small rock
				Rock * newSmallRock = new SmallRock;
				newSmallRock->changePoint(rocks[j]->getPoint().getX() + 32, rocks[j]->getPoint().getY());
				newSmallRock->setVelocity(rocks[j]->getVelocity());
				newSmallRock->setAngle(rocks[j]->getAngle());
				newSmallRock->setNewSpeed(2);
				rocks.push_back(newSmallRock);
				// add one point for breaking the rock
				score++;
				// add an explosion for good times
				Explosion * explosion = new Explosion;
				explosion->setPoint(rocks[j]->getPoint());
				explosions.push_back(explosion);
			}
			// if the rock is medium sized
			else if (rocks[j]->getSize() == "medium")
			{
				// break it into two smaller rocks
				Rock * newSmallRock1 = new SmallRock;
				newSmallRock1->changePoint(rocks[j]->getPoint().getX() + 16, rocks[j]->getPoint().getY());
				newSmallRock1->setVelocity(rocks[j]->getVelocity());
				newSmallRock1->setAngle(rocks[j]->getAngle());
				newSmallRock1->setNewSpeed(3);
				rocks.push_back(newSmallRock1);
				Rock * newSmallRock2 = new SmallRock;
				newSmallRock2->changePoint(rocks[j]->getPoint().getX() - 16, rocks[j]->getPoint().getY());
				newSmallRock2->setVelocity(rocks[j]->getVelocity());
				newSmallRock2->setAngle(rocks[j]->getAngle());
				newSmallRock2->setNewSpeed(-3);
				rocks.push_back(newSmallRock2);
				// give the user two points
				score += 2;
				// add an explosion for effect
				Explosion * explosion = new Explosion;
				explosion->setPoint(rocks[j]->getPoint());
				explosions.push_back(explosion);
			}
			// if the rock is small
			else if (rocks[j]->getSize() == "small")
			{
				// just add the explosion and give them three points
				Explosion * explosion = new Explosion;
				explosion->setPoint(rocks[j]->getPoint());
				explosions.push_back(explosion);
				score += 3;
			}
			// the ship dies
			ship.kill();
		}
	}
	// now check for a hit (if it is close enough to any live bullets)
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isAlive())
		{
			// this bullet is alive, see if its too close

			// check if the rock is at this point (in case it was hit)
			for (int j = 0; j < rocks.size(); j++)
			{
				if (rocks[j]->isAlive())
				{
					// BTW, this logic could be more sophisiticated, but this will
					// get the job done for now...
					if (fabs(bullets[i]->getPoint().getX() - rocks[j]->getPoint().getX()) < CLOSE_ENOUGH
						&& fabs(bullets[i]->getPoint().getY() - rocks[j]->getPoint().getY()) < CLOSE_ENOUGH)
					{
						//we have a hit!
						rocks[j]->hit();
						// hit the rock
						if (rocks[j]->getSize() == "big")
						{
							// break it into two medium rocks
							Rock * newMediumRock1 = new MediumRock;
							newMediumRock1->changePoint(rocks[j]->getPoint().getX(), rocks[j]->getPoint().getY() + 32);
							newMediumRock1->setVelocity(rocks[j]->getVelocity());
							newMediumRock1->setAngle(rocks[j]->getAngle());
							newMediumRock1->setFirst(true);
							rocks.push_back(newMediumRock1);
							Rock * newMediumRock2 = new MediumRock;
							newMediumRock2->changePoint(rocks[j]->getPoint().getX(), rocks[j]->getPoint().getY() - 32);
							newMediumRock2->setVelocity(rocks[j]->getVelocity());
							newMediumRock2->setAngle(rocks[j]->getAngle());
							newMediumRock2->setFirst(false);
							rocks.push_back(newMediumRock2);
							// and one small rock
							Rock * newSmallRock = new SmallRock;
							newSmallRock->changePoint(rocks[j]->getPoint().getX() + 32, rocks[j]->getPoint().getY());
							newSmallRock->setVelocity(rocks[j]->getVelocity());
							newSmallRock->setAngle(rocks[j]->getAngle());
							newSmallRock->setNewSpeed(2);
							rocks.push_back(newSmallRock);
							score++; // give them some lovin
							// add an explosion to get the heart racing
							Explosion * explosion = new Explosion;
							explosion->setPoint(rocks[j]->getPoint());
							explosions.push_back(explosion);
						}
						// if they hit a medium rock
						else if (rocks[j]->getSize() == "medium")
						{
							// break it into two smaller ones
							Rock * newSmallRock1 = new SmallRock;
							newSmallRock1->changePoint(rocks[j]->getPoint().getX() + 32, rocks[j]->getPoint().getY());
							newSmallRock1->setVelocity(rocks[j]->getVelocity());
							newSmallRock1->setAngle(rocks[j]->getAngle());
							newSmallRock1->setNewSpeed(3);
							rocks.push_back(newSmallRock1);
							Rock * newSmallRock2 = new SmallRock;
							newSmallRock2->changePoint(rocks[j]->getPoint().getX() - 32, rocks[j]->getPoint().getY());
							newSmallRock2->setVelocity(rocks[j]->getVelocity());
							newSmallRock2->setAngle(rocks[j]->getAngle());
							newSmallRock2->setNewSpeed(-3);
							rocks.push_back(newSmallRock2);
							score += 2; // give love
							// and throw an explosion in their face
							Explosion * explosion = new Explosion;
							explosion->setPoint(rocks[j]->getPoint());
							explosions.push_back(explosion);
						}
						// if they hit a wee one
						else if (rocks[j]->getSize() == "small")
						{
							score += 3; // give some love
							// show some action
							Explosion * explosion = new Explosion;
							explosion->setPoint(rocks[j]->getPoint());
							explosions.push_back(explosion);
						}

						// the bullet is dead as well
						bullets[i]->kill();
					}
				}
			}
		} // if bullet is alive

	} // for bullets
}

/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Remove any dead objects (take bullets out of the list, deallocate rock)
**************************************************************************/
void Game::cleanUpZombies()
{
	// if the ship is dead, get him off screen
	if (!ship.isAlive())
	{
		Point getOuttaHere(2000,2000);
		ship.setPoint(getOuttaHere);
	}

	// check for dead rock
	vector<Rock *>::iterator rockIt = rocks.begin();
	while (rockIt != rocks.end())
	{
		Rock * pRock = *rockIt;

		if (!pRock->isAlive())
		{
			delete pRock;
			pRock = NULL;
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			rockIt++; // advance
		}
	}

	// Look for dead bullets
	vector<Bullet *>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet * pBullet = *bulletIt;

		if (!pBullet->isAlive())
		{
			// remove from list and 
			delete pBullet;
			pBullet = NULL;
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
		}
	}

	// Look for dead explosions
	vector<Explosion *>::iterator explosionIt = explosions.begin();
	while (explosionIt != explosions.end())
	{
		Explosion * pExplosion = *explosionIt;

		if (!pExplosion->isAlive())
		{
			// remove from list and 
			delete pExplosion;
			pExplosion = NULL;
			explosionIt = explosions.erase(explosionIt);
		}
		else
		{
			explosionIt++; // advance
		}
	}

}

/***************************************
* GAME :: HANDLE INPUT
* accept input from the user
***************************************/
void Game::handleInput(const Interface & ui)
{
	if (ui.isEnter())
	{
		play = true;
	}
	if (ship.isAlive())
	{
		if (ui.isLeft())
		{
			ship.moveLeft();
		}

		if (ui.isRight())
		{
			ship.moveRight();
		}

		if (ui.isUp())
		{
			ship.applyThrust();
		}

		// Check for "Spacebar
		if (ui.isSpace())
		{
			Bullet * newBullet = new Bullet;
			newBullet->fire(ship.getPoint(), ship.getAngle(), ship.getVelocity());
			bullets.push_back(newBullet);
		}
	}
}

/*********************************************
* GAME :: DRAW
* Draw everything on the screen
*********************************************/
void Game::draw(const Interface & ui)
{
	if (play)
	{
		// Check if you have a valid rock and if it's alive
		// then call it's draw method
		for (int i = 0; i < rocks.size(); i++)
		{
			if (rocks[i]->isAlive())
				rocks[i]->draw();
		}

		// draw the ship
		if (ship.isAlive())
			ship.draw();

		// draw the bullets, if they are alive
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->isAlive())
			{
				bullets[i]->draw();
			}
		}

		// draw the explosions, if they are alive
		for (int i = 0; i < explosions.size(); i++)
		{
			if (explosions[i]->isAlive())
			{
				explosions[i]->draw();
			}
		}

		// Put the score on the screen
		Point scoreLocation;
		scoreLocation.setX(topLeft.getX() + 5);
		scoreLocation.setY(topLeft.getY() - 5);

		drawNumber(scoreLocation, score);
	} 
	else
	{
		Point top(-45, 50);
		char text1[256] = "-=Asteroids=-";
		drawText(top, text1);
		Point bottom(-55, -50);
		char text3[256] = "Press \"P\" to Play";
		drawText(bottom, text3);
	}
}


// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
/*
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}
*/

