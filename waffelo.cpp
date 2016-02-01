// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and MOVE
// Chapter 6 Waffelo.cpp v1.0
// This class is the core of the game

#include "waffelo.h"

//=============================================================================
// Constructor
//=============================================================================
Waffelo::Waffelo()
{}

//=============================================================================
// Destructor
//=============================================================================
Waffelo::~Waffelo()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Waffelo::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	bool jump = false;
	
	// Background texture
    if (!backgroundTexture.initialize(graphics,BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background texture"));

    // cake textures
    if (!cakeTexture.initialize(graphics,CAKES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cake texture"));

	// waffle collectible texture
	if (!waffleCollectibleTexture.initialize(graphics, WAFFLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cake texture"));
	
    
	// Background image
	if (!background.initialize(graphics,0,0,0,&backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background image"));

    // Cake image
    if (!cake.initialize(this, cakeNS::WIDTH, cakeNS::HEIGHT, cakeNS::TEXTURE_COLS, &cakeTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cake image"));
		
	// Waffle image
	if (!waffle.initialize(this, waffleCollectibleNS::WIDTH, waffleCollectibleNS::HEIGHT, 4, &waffleCollectibleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cake image"));


	// bubble init
	bubbleImage.setFrames(cakeNS::BUBBLE_START_FRAME, cakeNS::BUBBLE_END_FRAME);
	bubbleImage.setCurrentFrame(cakeNS::BUBBLE_START_FRAME);
	bubbleImage.setFrameDelay(cakeNS::BUBBLE_ANIMATION_DELAY);
	bubbleImage.setLoop(true);                  // loop animation

	/*
    // ship
    if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH/4);
    ship1.setY(GAME_HEIGHT/4);
    ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)
    // ship2
    if (!ship2.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2"));
    ship2.setFrames(shipNS::SHIP2_START_FRAME, shipNS::SHIP2_END_FRAME);
    ship2.setCurrentFrame(shipNS::SHIP2_START_FRAME);
    ship2.setX(GAME_WIDTH - GAME_WIDTH/4);
    ship2.setY(GAME_HEIGHT/4);
    ship2.setVelocity(VECTOR2(-shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)
	*/

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Waffelo::update()
{
	cake.setFrames(0, 1);

	//MOVE START
	// if move right
	if (input->isKeyDown(CAKE_RIGHT_KEY))            
	{

		cake.setFrames(2,3);
		velocity.x += 200;		
		cake.setX(cake.getX() + frameTime * velocity.x);
		if (cake.getX() >= midpoint)
		{
			cake.setX(midpoint);
			background.setX(background.getX() - frameTime * velocity.x *0.5f);
			waffle.setX(waffle.getX() - frameTime * velocity.x);
		}
		cake.flipHorizontal(false);
	}

	if (!input->isKeyDown(CAKE_RIGHT_KEY))
	{
		//cake.setFrames(0, 1);
		velocity.x = 0;
		cake.setX(cake.getX() + frameTime * velocity.x);
	}
	if (cake.getX() > GAME_WIDTH)               // if off screen right
		cake.setX((float)-cake.getWidth()); // position off screen left


	// if move left
	if (input->isKeyDown(CAKE_LEFT_KEY))             
	{
		cake.setFrames(2, 3);
		velocity.x -= 200;
		cake.setX(cake.getX() + frameTime * velocity.x);
		background.setX(background.getX() - frameTime * velocity.x *0.5f);
		if (background.getX() > 0)
		{
			background.setX(0);
		}
		cake.flipHorizontal(true);
	}

	if (!input->isKeyDown(CAKE_LEFT_KEY))
	{
		//cake.setFrames(0, 1);
		velocity.x = 0;
		cake.setX(cake.getX() + frameTime * velocity.x);
	}
	if (cake.getX() < -cake.getWidth())         // if off screen left
		cake.setX((float)GAME_WIDTH);      // position off screen right
	//MOVE END




	//if jump
	//START JUMP
	if (input->isKeyDown(CAKE_UP_KEY))
	{
		jump = true;	
		velocity.y = -JumpForce;
		//cake.setFrames(4, 5);
		cake.setCurrentFrame(4);
	}

	if (jump)
	{
		cake.setY(cake.getY() +frameTime * velocity.y);
		velocity.y += gravity;
		if (velocity.y == 0)
		{
			cake.setCurrentFrame(6);
		}
	}
	//END JUMP


	//IF SHRINK
	//SHRINK START
	if (shrink == true && cake.getScale() >= 0.5)
	{
		cake.setScale(cake.getScale() - frameTime * SCALE_RATE);
	}

	//cake.DeactivatePower(&shrink);

	/*if (shrink == false && cake.getScale() <= 1)
	{
		cake.setScale(cake.getScale() + frameTime * SCALE_RATE);
	}*/
	//SHRINK END

	//BUBBLE START

	//BUBBLE END

    cake.update(frameTime);
	waffle.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Waffelo::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Waffelo::collisions()
{
    VECTOR2 collisionVector;
    // if collision between ship and planet
    if(cake.collidesWith(waffle, collisionVector))
    {
		cake.ActivatePower(&shrink);
		//cake.ActivatePower(&bubble);
        //waffle.bounce(collisionVector, cake);
        //cake.damage(waffle);
    }

   /* // if collision between ships
    if(ship1.collidesWith(ship2, collisionVector))
    {
        // bounce off ship
        ship1.bounce(collisionVector, ship2);
        ship1.damage(SHIP);
        // change the direction of the collisionVector for ship2
        ship2.bounce(collisionVector*-1, ship1);
        ship2.damage(SHIP);
	}*/
}

//=============================================================================
// Render game items
//=============================================================================
void Waffelo::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    background.draw();                          // add the orion nebula to the scene
    cake.draw();   
	waffle.draw();
    
    graphics->spriteEnd();                  // end drawing sprites

	if (bubble == true)
	{
		// draw shield using colorFilter 50% alpha
		bubbleImage.draw();//graphicsNS::ALPHA50);
	}
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Waffelo::releaseAll()
{
    backgroundTexture.onLostDevice();
    cakeTexture.onLostDevice();
	waffleCollectibleTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Waffelo::resetAll()
{
    cakeTexture.onResetDevice();
    backgroundTexture.onResetDevice();
	waffleCollectibleTexture.onResetDevice();
    Game::resetAll();
    return;
}

