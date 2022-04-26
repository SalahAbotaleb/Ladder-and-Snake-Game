#pragma once
#include "Action.h"

class AddSnake : public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition startPos; // 1- The start position of the Snake
	CellPosition endPos;   // 2- The end position of the Snake
	bool valid; // boolean set to true if snake can be added to given cell position
	// Note: These parameters should be read in ReadActionParameters()

public:

	AddSnake(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddSnake action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new Snake Object 
							// then Sets this Snake object to the GameObject Pointer of its Cell

	virtual ~AddSnake(); // Virtual Destructor

};

