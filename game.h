/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "rocks.h"
#include "ship.h"
#include "explosion.h"


#define CLOSE_ENOUGH 15


 /*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
	/*********************************************
	* Constructor
	* Initializes the game
	*********************************************/
	Game(Point tl, Point br);
	~Game();

	/*********************************************
	* Function: handleInput
	* Description: Takes actions according to whatever
	*  keys the user has pressed.
	*********************************************/
	void handleInput(const Interface & ui);

	/*********************************************
	* Function: advance
	* Description: Move everything forward one
	*  step in time.
	*********************************************/
	void advance();

	/*********************************************
	* Function: draw
	* Description: draws everything for the game.
	*********************************************/
	void draw(const Interface & ui);


	bool getPlay() { return play; }

private:
	// The coordinates of the screen
	Point topLeft;
	Point bottomRight;

	int score;

	Ship ship;
	std::vector<Bullet *> bullets;
	std::vector<Explosion *> explosions;

	std::vector <Rock *> rocks;
	Rock * rock;
	bool play;

	/*************************************************
	* Private methods to help with the game logic.
	*************************************************/
	bool isOnScreen(const Point & point); 
	void advanceExplosions();
	void advanceBullets();
	void advanceRock();
	Rock* createBigRock();

	void handleCollisions();
	void cleanUpZombies();
};

#endif /* GAME_H */

