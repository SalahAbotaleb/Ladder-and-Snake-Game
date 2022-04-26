#include "OpenGrid.h"
OpenGrid::OpenGrid(ApplicationManager* pApp) :Action(pApp)
{
	//when opening a new grid one of the necessary clean ups is to re-intialize the isSet flags with there
	//initial value to be able to load cards 9,10,11 with there new values 
	CardNine::reset_is_Set();
	CardTen::reset_is_Set();
	CardEleven::reset_is_Set();
}
void OpenGrid::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter the file name to load data from:"); //getting name of file 
	name = pIn->GetString(pOut);
	InFile.open(name+".txt");
	pOut->ClearStatusBar();
}
void OpenGrid::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	if (!InFile.is_open()) //in case of file is not found in the folder
	{
		pGrid->PrintErrorMessage("The file name entered is not found, Click anywhere to continue");
		pOut->ClearStatusBar();
		return;
	}
	pGrid->ClearGrid();
	int ladderCount, SnakeCount, CardCount; //variables to store count of game objects
	if (InFile.eof())
		return;
	InFile >> ladderCount;
	for (int i = 0;i < ladderCount;i++) //loading ladder's data 
	{
		GameObject* pLadder = new Ladder(CellPosition(0),CellPosition(0)); //creating empty object
		pLadder->Load(InFile, ladder);
		pGrid->AddObjectToCell(pLadder);
	}
	if (InFile.eof())
		return;
	InFile >> SnakeCount;
	for (int i = 0;i < SnakeCount;i++)
	{
		GameObject* pSnake = new Snake(CellPosition(0), CellPosition(0)); //creating empty object
		pSnake->Load(InFile, snake);
		pGrid->AddObjectToCell(pSnake);
	}
	if (InFile.eof())
		return;
	InFile >> CardCount;
	for (int i = 0;i < CardCount;i++)
	{
		int cardNumber;
		InFile >> cardNumber;
		GameObject* pCard;
		switch (cardNumber) //switch case to create empty card of specific number
		{
			
		case 1:
			pCard = new CardOne(0);
			break;
		case 2:
				pCard = new CardTwo(0);
				break;
		case 3:
			pCard = new CardThree(0);
			break;
		case 4:
			pCard = new CardFour(0);
			break;
		case 5:
			pCard = new CardFive(0);
			break;
		case 6:
			pCard = new CardSix(0);
			break;
		case 7:
			pCard = new CardSeven(0);
			break;
		case 8:
			pCard = new CardEight(0);
			break;
		case 9:
			pCard = new CardNine(0);
			break;
		case 10:
			pCard = new CardTen(0);
			break;
		case 11:
			pCard = new CardEleven(0);
			break;
		case 12:
			pCard = new CardTwelve(0);
			break;
		
		}
		pCard->Load(InFile, card);
		pGrid->AddObjectToCell(pCard);
	}
	InFile.close();
	pGrid->PrintErrorMessage("Successsfully Loaded the grid, Click anywhere to continue");
	pOut->ClearStatusBar();
}

OpenGrid::~OpenGrid()
{
	
}
