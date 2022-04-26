#include "NewGame.h"
#include "Grid.h"


NewGame::NewGame(ApplicationManager* pApp):Action(pApp) {}		//constructor
void NewGame::ReadActionParameters(){}

void NewGame::Execute() 
{
	Grid* pGrid = pManager->GetGrid();
	pGrid->NewGame();											//Restarts players' positions, wallets,turn returns to player 0
} 
NewGame::~NewGame(){}											//destructor
