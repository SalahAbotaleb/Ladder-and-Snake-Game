#include "Snake.h"

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
	SnakeCount++;
	///TODO: Do the needed validation
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a Snake. Click to continue ..." and wait mouse click

	pGrid->PrintErrorMessage("You have reached a Snake. Click to continue ...");

	// 2- Apply the Snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	GameObject* Object = pGrid->CurrentCellObject(endCellPos);
	if (Object) //if the  player moved to cell contains a card
	{
		Object->Apply(pGrid, pPlayer); //apply the effect of this card
	}
}

void Snake::SetEndcell(CellPosition CP)
{
	endCellPos = CP;
}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

void Snake::Load(ifstream& Infile, Object_Type obj)
{
	if (obj != snake)
		return;
	CellPosition CP;
	int startcell;
	int endcell;
	Infile >> startcell >> endcell;
	SetEndcell(CellPosition(endcell)); //setting endcell with loaded value from file
	position = CellPosition(startcell);// setting startcell with loaded value from file
}

void Snake::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != snake)
		return;
	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}

int Snake::GetObjectCount()
{
	return SnakeCount;
}
int Snake::SnakeCount = 0;
Snake::~Snake()
{
	SnakeCount--;
}