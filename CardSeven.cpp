#include "CardSeven.h"

CardSeven::CardSeven(const CellPosition& pos) :Card(pos)
{
	CardCount++;
	cardNumber = 7; // initialise card number to 7
}
const CellPosition CardSeven::firstCell(1); // initialise firstcell member to first cell in grid

void CardSeven::ReadCardParameters(Grid* pGrid)
{
	// no parameters to read
}

Card* CardSeven::PasteCard()
{
	//create and retuen a new object to be added to grid
	Card* copy = new CardSeven(0);
	return copy;
}

Card* CardSeven::CopyCard()
{
	// create and return a new object to be added to clipboard
	CardSeven* copy = new CardSeven(0);
	// decrement card count as acrd was not added to grid
	CardCount--;
	return copy;
}
void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer); // calls apply of base class

	// gets next player 
	Player* next = pGrid->GetNextPlayer(position);

	if (next) // if found reset all players in the cell
	{
		CellPosition nextpos = next->GetCell()->GetCellPosition();
		for (int i = 0; i < 4; i++)
		{
			Player* another = pGrid->CheckCurrentCellPlayer(nextpos, i);
			if (another)
			{ 
				//move all players to first cell using updateplayercell() function in grid
				pGrid->UpdatePlayerCell(another,firstCell)  ;
			}
			
		}
	}
}

void CardSeven::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Save(OutFile, obj);
	OutFile << endl;
}

CardSeven::~CardSeven()
{
	CardCount--; // decrement card count when deleted
}
