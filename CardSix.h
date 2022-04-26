#pragma once
#include "Card.h"
class CardSix : public Card
{
	CellPosition CP;  // the position that the player will move to 
public:
	CardSix(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardSix which is: cell position to move to

	virtual Card* PasteCard();
	virtual Card* CopyCard();

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardSix on the passed Player
													// if there is a gameobject its effect will be implemented
	virtual void Load(ifstream& Infile, Object_Type obj);
	virtual void Save(ofstream& OutFile, Object_Type obj);
	virtual ~CardSix(); // A Virtual Destructor
};

