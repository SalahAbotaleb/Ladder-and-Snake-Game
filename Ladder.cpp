#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
	LadderCount++;
	///TODO: Do the needed validation
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}
void Ladder::SetEndcell(CellPosition CP)
{
	endCellPos = CP;
}
void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	 GameObject* Object = pGrid->CurrentCellObject(endCellPos);
	 if (Object) //if the  player moved to cell contains a card
	 {
		 Object->Apply(pGrid,pPlayer); //apply the effect of this card
	 }
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}
void Ladder::Load(ifstream& Infile, Object_Type obj)
{
	if (obj != ladder)
		return;
	CellPosition CP;
	int startcell;
	int endcell;
	Infile >> startcell >> endcell;
	SetEndcell(CellPosition(endcell)); //setting endcell with loaded value from file
	position = CellPosition(startcell);// setting startcell with loaded value from file
}
int Ladder::LadderCount = 0;
void Ladder::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != ladder)
		return;
	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}
int Ladder::GetObjectCount()
{
	return LadderCount;
}
Ladder::~Ladder()
{
	LadderCount--;
}
