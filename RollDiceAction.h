#pragma once

#include "Action.h"

class RollDiceAction : public Action
{

	// No parameters for this action

public:
	RollDiceAction(ApplicationManager *pApp); // constructor for rolldiceaction 

	virtual void ReadActionParameters(); // virtual function with no parameters to read

	virtual void Execute(); // rolls dice and move player

	virtual ~RollDiceAction(); // virtual destructor
};

