#include "CardThree.h"


CardThree::CardThree(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	CardCount++;
	cardNumber = 3; 
}
void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{ 
	Card::Apply(pGrid, pPlayer);			// output card number

	Output* pOut = pGrid->GetOutput();
	
	pGrid->PrintErrorMessage("You won an extra dice roll! click to continue" );

	pPlayer->SetDoNotPlay(-1);				/*DoNotPlay is a data member in Player used to indicate if the player has an
											extra dice roll(-1),cancelled dice roll (1) or in the prision(3)
											if DoNotPlay=0 he will play normally */

	pOut->ClearStatusBar();
}

Card* CardThree::PasteCard()
{
	Card* copy = new CardThree(0);
	return copy;
}

Card* CardThree::CopyCard()
{
	Card* copy = new CardThree(0);
	CardCount--;
	return copy;
}

void CardThree::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Save(OutFile, obj);
	OutFile  << endl;
}

CardThree::~CardThree(void)
{
	CardCount--;
}
