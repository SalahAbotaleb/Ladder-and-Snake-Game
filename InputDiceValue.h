#pragma once
#include "Action.h"
class InputDiceValue : public Action
{
	int dicevalue; // entered dice number to be played
public:

	InputDiceValue(ApplicationManager* pApp); // constructor

	virtual void ReadActionParameters(); // read dicevalue from the user

	virtual void Execute(); // move player by given dice value

	virtual ~InputDiceValue(); //virtual destructor
};

