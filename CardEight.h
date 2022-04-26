#pragma once
#include "card.h"
class CardEight :
	public Card
{
		int Bail; // the wallet value to decrease from the player if he chose to
public:

	CardEight(const CellPosition & pos);							//constructor

	virtual void Apply(Grid* pGrid, Player* pPlayer);				//prints a message then checks if the player will pay the bail 
																	//or he won't be able to move for three turns

	virtual void ReadCardParameters(Grid * pGrid);					// Reads the parameters of CardThree which is: Bail
	virtual Card* PasteCard();										//used to take the copied card from the clipboard to grid
	virtual Card* CopyCard();										//used to take a copy from the selected card to the clipboard
	virtual void Load(ifstream& Infile, Object_Type obj);			//virtual function used to load objects
	virtual void Save(ofstream& OutFile, Object_Type obj);			//virtual function used to save objects
	~CardEight(void);												//destructor

};
