#pragma once
#include "card.h"
class CardFour :
	public Card
{
public:
	CardFour(const CellPosition& pos);							//Constructor
	virtual void Apply(Grid* pGrid, Player* pPlayer);			//prints a message then sets DoNotPlay to 1
	virtual Card* PasteCard();									//used to take the copied card from the clipboard to grid
	virtual Card* CopyCard();									//used to take a copy from the selected card to the clipboard
	virtual void Save(ofstream& OutFile, Object_Type obj);		//virtual function used to save objects
	~CardFour(void);											//destructor
};