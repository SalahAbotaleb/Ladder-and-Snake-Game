#pragma once

#include "Card.h"

class CardTwo :	public Card
{

public:
	CardTwo(const CellPosition & pos); // A Constructor takes card position


	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual void Save(ofstream& OutFile, Object_Type obj);
	virtual	Card* PasteCard();
	virtual Card* CopyCard();
	virtual ~CardTwo(); // A Virtual Destructor
};
