// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 Cake.cpp v1.0

#include "cake.h"

//=============================================================================
// default constructor
//=============================================================================
Cake::Cake() : Entity()
{
    spriteData.width = cakeNS::WIDTH;           // size of cake1
    spriteData.height = cakeNS::HEIGHT;
    spriteData.x = cakeNS::X;                   // location on screen
    spriteData.y = cakeNS::Y;
    spriteData.rect.bottom = cakeNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = cakeNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = cakeNS::CAKE_ANIMATION_DELAY;
    startFrame = cakeNS::CAKE_START_FRAME;     // first frame of cake animation
    endFrame     = cakeNS::CAKE_END_FRAME;     // last frame of cake animation
    currentFrame = startFrame;
	radius = 48;//cakeNS::WIDTH/2.0;
	waffleBubble = false;
    mass = cakeNS::MASS;
    collisionType = entityNS::CIRCLE;

}

//=============================================================================
// Initialize the Cake.
// Post: returns true if successful, false if failed
//=============================================================================
bool Cake::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    //idle.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
    /*idle.setFrames(cakeNS::MOVE_START_FRAME, cakeNS::MOVE_END_FRAME);
	idle.setCurrentFrame(cakeNS::MOVE_START_FRAME);
	idle.setFrameDelay(cakeNS::MOVE_ANIMATION_DELAY);
	idle.setLoop(false);                  // do not loop animation*/
	bubble.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	bubble.setFrames(cakeNS::BUBBLE_START_FRAME, cakeNS::BUBBLE_END_FRAME);
	bubble.setCurrentFrame(cakeNS::BUBBLE_START_FRAME);
	bubble.setFrameDelay(cakeNS::BUBBLE_ANIMATION_DELAY);
	bubble.setLoop(true);                  // loop animation

    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the cake
//=============================================================================
void Cake::draw()
{
    Image::draw();              // draw cake
	if (waffleBubble == true)
	{
		// draw shield using colorFilter 50% alpha
		bubble.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
	}


}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Cake::update(float frameTime)
{
    Entity::update(frameTime);
    //spriteData.angle += frameTime * cakeNS::ROTATION_RATE;  // rotate the cake
    spriteData.x += frameTime * velocity.x;         // move cake along X 
    spriteData.y += frameTime * velocity.y;         // move cake along Y

    //Bounce off walls
    if (spriteData.x > GAME_WIDTH-cakeNS::WIDTH)    // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH-cakeNS::WIDTH;    // position at right screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    }
    if (spriteData.y > GAME_HEIGHT-cakeNS::HEIGHT)  // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT-cakeNS::HEIGHT;  // position at bottom screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }

	//currentState->updateState();
}

//=============================================================================
// damage
//=============================================================================
void Cake::damage(WEAPON weapon)
{

}
/*void Cake::changeSprite(int x, int y)
{
	startframe = x;
	cakeNS::CAKE_END_FRAME = y;
}*/

/*void Cake::changeState(const State* newState)
{
	delete currentState;
	currentState = newState;
}*/

void Cake::ActivatePower(bool *power)
{
	*power = true;
}

void Cake::DeactivatePower(bool *power)
{
	*power = false;
}