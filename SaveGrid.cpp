#include "SaveGrid.h"

SaveGrid::SaveGrid(ApplicationManager* pApp) :Action(pApp)
{
}

void SaveGrid::ReadActionParameters()
{
	Grid *pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter the file name to save data into:");
	name=pIn->GetString(pOut); //get the file name from the user
	OutFile.open(name+".txt"); // opening the file for output
	pOut->ClearStatusBar();
}

void SaveGrid::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int ladderCount, SnakeCount, CardCount; //variables to store count of game objects
	ladderCount = pGrid->GetLadderCount();// storing the number of occurance
	SnakeCount = pGrid->GetSnakeCount();
	CardCount = pGrid->GetCardCount();
	OutFile << ladderCount << endl; //printing as required file format
	pGrid->SaveAll(OutFile, ladder); //calling SaveAll in Grid to be able to Call Save of ladder objects in the cell list
	OutFile << SnakeCount << endl;
	pGrid->SaveAll(OutFile, snake); //calling SaveAll in Grid to be able to Call Save of snake objects in the cell list
	OutFile << CardCount << endl;
	pGrid->SaveAll(OutFile, card);//calling SaveAll in Grid to be able to Call Save of card objects in the cell list
	OutFile.close(); //closing the opened file 
	pGrid->PrintErrorMessage("Successsfully saved the grid, Click anywhere to continue");
}

SaveGrid::~SaveGrid()
{
	//we need at the end of save action to reset issaved parameter in cards 9,10,11 because
	//user may want to save again in the same program execution so to be able to execute SaveGrid again
	//the variables assosiated with saving must be reseted to its intial value
	CardNine::reset_is_saved();
	CardTen::reset_is_saved();
	CardEleven::reset_is_saved();
}
