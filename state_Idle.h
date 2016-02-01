// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 cake.h v1.0

#ifndef _State_Idle_H                 // Prevent multiple definitions if this 
#define _State_Idle_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "State.h"
#include "cake.h"

class State_Idle : public State
{
public:
	void Execute()
	{
		cakeNS::CAKE_START_FRAME = 0;
		cakeNS::CAKE_END_FRAME = 1;
	}// call the idle animation
		
};
#endif