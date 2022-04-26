#include "Card.h"

Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

void Card::SetCardNumber(int cnum)
{
	if(cnum>0&&cnum<=12) //valaditing the card number is between 1 to 12 inclusive
	cardNumber = cnum; 
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{
	pOut->DrawCell(position,cardNumber); //Drawing the cell with cardNumber passed to function

}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}
void Card::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != card)
		return;
	OutFile << cardNumber << " " << position.GetCellNum() << " "; // output the card num and it's cell becacuse this step will be printed for all Cards therefore it's implemented in base class
																	//special output parameters is implemented to suit each card
}

int Card::GetObjectCount()
{
	return CardCount;
}

void Card::Load(ifstream& Infile, Object_Type obj)
{
	if (obj != card)
		return;

	int  cposition;
	Infile>>cposition;
	
	position = CellPosition::GetCellPositionFromNum(cposition);// setting the cell position to the correspoding cellnumber that is found in the load file
																//Special input parameters is implemented for each card load
}
void Card::SetCardPos(CellPosition &pos)
{
	position = pos;	
}
void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}
int Card::CardCount = 0;
Card::~Card()
{
}

void Card::IncrementCardCount()
{
	CardCount++;
}
