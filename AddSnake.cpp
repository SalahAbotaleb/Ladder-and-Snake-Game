#include "AddSnake.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"

AddSnake::AddSnake(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	valid = 1;// initialize the valid member to true
}


AddSnake::~AddSnake()
{
}

void AddSnake::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();




	///TODO: Make the needed validations on the read parameters
	
	if (!startPos.IsValidCell() || !endPos.IsValidCell())  // check if start or end cells are valid
	{
		//error
		valid = 0; // change valid to false so it cannot be added
		pGrid->PrintErrorMessage("Error: Snake cannot be added outside grid! Click to continue ...");
	}
	else if (startPos.GetCellNum() == 99) // checks if start position is the last cell of grid
	{
		valid = 0;
		pGrid->PrintErrorMessage("Error: Cannot add snkae to last cell! Click to continue ...");
	}
	else if (startPos.GetCellNum() <= endPos.GetCellNum()) // checks if endcell below after start cell
	{
		//error
		valid = 0;
		pGrid->PrintErrorMessage("Error: Start cell cannot exceed end cell! Click to continue ...");
	}
	else if (startPos.HCell() != endPos.HCell()) // checks if snake is placed in one column
	{
		//error
		valid = 0;
		pGrid->PrintErrorMessage("Error: start cell and endcell cannot be in a different column! Click to continue ...");
	}
	else if (pGrid->CurrentCellLadder(endPos) != NULL) // checks if the endcell contains a ladder
	{
		valid = 0;
		pGrid->PrintErrorMessage("Error: endcell cannot contain ladder! Click to continue ...");
	}
	else if (pGrid->CurrentCellSnake(endPos) != NULL) // checks if endcell contains a snake
	{
		valid = 0;
		pGrid->PrintErrorMessage("Error: endcell cannot contain snake! Click to continue ...");
	}
	else
	{
		CellPosition col(0, startPos.HCell()); // create cellposition object to first row of ladder column
		for (int i = 0; i <= 8; i++)
		{
			// loops over cellpositions of Snake column and gets all objects in the column
			GameObject* snake = pGrid->CurrentCellSnake(col);

			GameObject* ladder = pGrid->CurrentCellLadder(col);

			if (ladder) // check if start position is an end of a ladder if found
			{
				CellPosition ladderEnd = dynamic_cast<Ladder*>(ladder)->GetEndPosition(); // get cellposition end of ladder
				if (startPos.GetCellNum() == ladderEnd.GetCellNum())
				{
					valid = 0;
					pGrid->PrintErrorMessage("Error: startcell cannot contain ladder! Click to continue ...");
				}

			}
			if (snake) // check for overlapping snakes if found
			{
				CellPosition snakeEnd = dynamic_cast<Snake*>(snake)->GetEndPosition();
				if (startPos.GetCellNum() == snakeEnd.GetCellNum())
				{
					valid = 0;
					pGrid->PrintErrorMessage("Error: startcell cannot contain snake! Click to continue ...");
				}
				if (endPos.GetCellNum() < col.GetCellNum() && startPos.GetCellNum() > snakeEnd.GetCellNum())
				{
					valid = 0;
					pGrid->PrintErrorMessage("Error: snakes cannot overlap! Click to continue ...");
				}
			}
			col.SetVCell(i + 1);
		}
	}
	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddSnake::Execute()
{

	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	if (!valid) // do not create snake when validation are not met
	{
		return;
	}
	// Create a Snake object with the parameters read from the user
	Snake* pSnake = new Snake(startPos, endPos);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		//delete the created snake
		delete pSnake;
	}
	// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnake

}
