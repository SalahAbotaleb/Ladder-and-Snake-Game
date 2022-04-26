#include "CardFive.h"
#include <iostream>

using namespace std;
CardFive::CardFive(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	CardCount++;
	cardNumber = 5; 
}

void CardFive::ReadCardParameters(Grid* pGrid) //Card five doesn't take parameters from user it immedietly applies its effect
{
}


void CardFive::Apply(Grid* pGrid, Player* pPlayer) {
		
 Card::Apply(pGrid, pPlayer);
 pGrid->PrintErrorMessage("You have reached card five. Go back with same amount you rolled");
	int diceValueRolled = pPlayer->GetRolledDiceNum(); //Get the rolled dice number to go back with the same amount

	CellPosition playerCellPosition = pPlayer->GetCell()->GetCellPosition(); //Get player position to go back again
	playerCellPosition.AddCellNum(-1 * diceValueRolled); // Multiply by -1 to go backwards
	pGrid->UpdatePlayerCell(pPlayer, playerCellPosition);  //Update player cell to move this player backwards
 GameObject* Object = pGrid->CurrentCellObject(playerCellPosition);
	 if (Object) //if the  player moved to cell contains an object
	 {
		 Object->Apply(pGrid,pPlayer); //apply the effect of this object
	 }
}

Card* CardFive::PasteCard()
{
	Card* copy = new CardFive(0);
	return copy;
}

Card* CardFive::CopyCard()
{
	CardFive* copy = new CardFive(0);
	CardCount--;
	return copy;
}

void CardFive::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Save(OutFile, obj);
	OutFile << endl;
}

CardFive::~CardFive(){
	CardCount--;
}



