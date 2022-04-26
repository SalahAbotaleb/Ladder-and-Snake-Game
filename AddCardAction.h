#pragma once

#include "Action.h"

class AddCardAction : public Action
{
	// [Action Parameters]
	int cardNumber;            // 1- the card number
	CellPosition cardPosition; // 2- cell position of the card
	bool Can_Add;  //This is a	flag indecates the avilability to add a card without violation to rules and allows Execute function to work 
	// Note: These parameters should be read in ReadActionParameters()
	
public:
	AddCardAction(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)
	
	virtual void Execute(); // Creates a new Card Object of the specific Card Number
	                        // and Reads the Parameters of This Card Number (if any)
	                        // then Sets this Card Object to GameObject Pointer of its Cell
							// Adds this card to the grid if it doesn't overlap another game object 
	virtual ~AddCardAction(); // A Virtual Destructor
};

