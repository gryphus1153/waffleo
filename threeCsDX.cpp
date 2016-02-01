// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.cpp v1.0

#include "threeCsDX.h"

//=============================================================================
// Constructor
//=============================================================================
ThreeCsDX::ThreeCsDX()
{
	// DirectX fonts
    dxFontMedium = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
ThreeCsDX::~ThreeCsDX()
{
    releaseAll();               // call deviceLost() for every graphics item
    SAFE_DELETE(dxFontMedium);
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void ThreeCsDX::initialize(HWND hwnd)
{
    Game::initialize(hwnd);
    graphics->setBackColor(graphicsNS::WHITE);

    // initialize DirectX fonts

    // 62 pixel high Arial
    if(dxFontMedium->initialize(graphics, 62, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    reset();            // reset all game variables
    fpsOn = true;       // display frames per second
    return;
}


//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void ThreeCsDX::reset()
{
    return;
}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void ThreeCsDX::update()
{
}

//=============================================================================
// render game items
//=============================================================================
void ThreeCsDX::render()
{
	const int BUF_SIZE = 20;
    static char buffer[BUF_SIZE];

    graphics->spriteBegin();

    dxFontMedium->setFontColor(graphicsNS::BLACK);
    dxFontMedium->print("Number of collisions",114,148);

    graphics->spriteEnd();


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void ThreeCsDX::releaseAll()
{
    dxFontMedium->onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void ThreeCsDX::resetAll()
{ 
    dxFontMedium->onResetDevice();
    Game::resetAll();
    return;
}
