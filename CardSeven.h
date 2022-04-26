#pragma once
#include "Card.h"
class CardSeven : public Card
{
	static const CellPosition firstCell; // constant cellposition to first cell of grid
public:
	CardSeven(const CellPosition& pos); // constructor

	virtual void ReadCardParameters(Grid* pGrid); // virtual function wih empty implementation
	virtual Card* PasteCard(); // function to create a new object to be added to grid when pasted
	virtual Card* CopyCard(); // function to create a neew object to be added to clipboard when copied
	virtual void Apply(Grid* pGrid, Player* pPlayer); //applies the card action to reset next player
	virtual void Save(ofstream& OutFile, Object_Type obj); // save card to file

	virtual ~CardSeven(); // virtual destructor
};

