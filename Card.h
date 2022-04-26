#pragma once

#include "GameObject.h"
#include "Player.h"

// Base Class of All Types of Cards (CardOne, CardTwo, CardThree, ...etc.)
// Note: We will make each type of Card in a separate class because:
// it may have additional data members and functions like: Apply(), ...etc. which have different implementation depending on Card Number
class Card : public GameObject
{
protected:
	int cardNumber; // an integer representing the card number
	static int CardCount; //A static variable to count the number of cards in the grid
public:
	
	Card(const CellPosition & pos); // A Constructor for card that takes the cell position of it

	void SetCardNumber(int cnum);   // The setter of card number
	int GetCardNumber();            // The getter of card number

	void Draw(Output* pOut) const;  // Draws the card number in the cell position of the card
	                                // It has the same implementation for all Card Types (Non-Virtual)

	virtual void ReadCardParameters(Grid * pGrid); // It reads the parameters specific for each Card Type
	                                               // It is a virtual function (implementation depends on Card Type)
	void SetCardPos(CellPosition &pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer);  // It applies the effect of the Card Type on the passed player
	                                                   // It is a virtual function (implementation depends on Card Type)

	//PasteCard() & CopyCard() has  diffrent implementations in card(1->12) classes(virtual)
	virtual Card* PasteCard()=0;		//used to take the copied card from the clipboard to grid
	virtual Card* CopyCard() = 0;		//used to take a copy from the selected card to the clipboard

	virtual void Load(ifstream& Infile, Object_Type obj);
	virtual void Save(ofstream& OutFile, Object_Type obj);
	static int GetObjectCount();
	void IncrementCardCount(); // increment card count by one
	virtual ~Card(); // A Virtual Destructor
	
};
