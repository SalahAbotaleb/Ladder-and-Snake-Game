#include "CardTwo.h"
#include <iostream>
#include "Ladder.h"

using namespace std;

CardTwo::CardTwo(const CellPosition &pos) : Card(pos) // set the cell position of the card
{
	CardCount++;
    cardNumber = 2;
}
void CardTwo::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Save(OutFile, obj);
	OutFile << endl;
}
Card* CardTwo::PasteCard()
{
    CardTwo* copy = new CardTwo(0);
    return copy;
}
Card* CardTwo::CopyCard()
{
    CardTwo* copy = new CardTwo(0);
    CardCount--;
    return copy;
}
void CardTwo::Apply(Grid *pGrid, Player *pPlayer)
{
    Card::Apply(pGrid, pPlayer);
    pGrid->PrintErrorMessage("You have reached card two. You will jump to the nearest ladder ahead of you");
    CellPosition playerCellPosition = pPlayer->GetCell()->GetCellPosition(); //Get the player position because it is needed to as a parameter to call the function get next ladder
    Ladder *pLadder = pGrid->GetNextLadder(playerCellPosition);// GetNextLadder function in grid class to send a pointer of the nearest ladder

    if (pLadder) //If pLadder pointed on something it means that there is really a ladder nearby
    {
        CellPosition LadderStartCell = pLadder->GetPosition(); // Set CellPosition object LadderStartCell with the starting cell of the ladder
        pGrid->UpdatePlayerCell(pPlayer, LadderStartCell); // Update the player cell to the start of the ladder
        pLadder->Apply(pGrid, pPlayer); //Take the ladder
    }
}
CardTwo::~CardTwo()
{
	CardCount--;
}
