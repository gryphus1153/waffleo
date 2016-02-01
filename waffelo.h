// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 Waffelo.h v1.0

#ifndef _WAFFELO_H             // Prevent multiple definitions if this 
#define _WAFFELO_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "planet.h"
#include "cake.h"
#include "waffleCollectible.h"
#include <iostream>

//=============================================================================
// This class is the core of the game
//=============================================================================
class Waffelo : public Game
{
private:
    // game items
    TextureManager backgroundTexture;   // background texture
    TextureManager cakeTexture;    // cake idle texture
	TextureManager waffleCollectibleTexture;
	
	Cake cake;           // Cake player
	WaffleCollectible waffle;
    Planet  planet;         // the planet
    Image   background;         // background image
	Image bubbleImage;

	UCHAR CAKE_RIGHT_KEY = VK_RIGHT;
	UCHAR CAKE_LEFT_KEY = VK_LEFT;
	UCHAR CAKE_UP_KEY = VK_UP;
	UCHAR CAKE_DOWN_KEY = VK_DOWN;

	//float Xvelocity = 0.0f;
	VECTOR2 velocity = cake.getVelocity();
	VECTOR2 deltaV = cake.getDeltaV();
	//float Yvelocity = 0.0f;

	const float CAKE_SPEED = 100.0f;                // pixels per second
	float midpoint = GAME_WIDTH / 2;
	bool jump = false;
	float JumpForce = 900.0f;
	float gravity = 25.0f;

	bool shrink;
	bool bubble;
	bool berry;
	bool jumpHigh;
	bool rocket;

public:
    // Constructor
    Waffelo();

    // Destructor
    virtual ~Waffelo();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
