#include "InputDiceValue.h"
#include "Grid.h"
#include "Player.h"

InputDiceValue::InputDiceValue(ApplicationManager* pApp) : Action(pApp)
{
}

void InputDiceValue::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Please enter a dice value between 1-6: ");

	dicevalue = pIn->GetInteger(pOut); // read dice number from the user

	while (dicevalue > 6 || dicevalue < 1) // validate dicevalue to be between 1 and 6
	{
		pGrid->PrintErrorMessage("Invalid dice value! click to continue ...");
		pOut->PrintMessage("Re-enter dice value"); // keeps entering dice value until it is between range
		dicevalue = pIn->GetInteger(pOut);
	}
	pOut->ClearStatusBar();
}

void InputDiceValue::Execute()
{
	// call read action parameters to read dice value
	ReadActionParameters();
	
	//get grid from pmanager
	Grid* pGrid = pManager->GetGrid();
	
	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	bool ended = pGrid->GetEndGame();
	if (ended)
	{
		return;
	}

	// Get the "current" player from pGrid
	Player* currentplayer = pGrid->GetCurrentPlayer();

	//Checking if the player is on card 4 or 8 ;so he can't move
	if (currentplayer->GetDoNotPlay() > 0)
	{
		//decreasing DoNotPlay
		currentplayer->SetDoNotPlay((currentplayer->GetDoNotPlay()) - 1);
		
		//calling move function setting dice roll to zero to increase turnCount
		currentplayer->Move(pManager->GetGrid(), 0);

		pGrid->AdvanceCurrentPlayer();
		return;
	}

	//if DoNotPlay=0,the player will play normally.

	//Move the currentPlayer using function Move of class player
	currentplayer->Move(pManager->GetGrid(), dicevalue);

	if (currentplayer->GetDoNotPlay() == -1) // check if player has an extra rolldice
	{
		currentplayer->SetDoNotPlay(0);
		//the player will return;thus the CurrentPlayer will not be advanced
		//(he will roll the dice again)
		return;
	}

	// Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();
}

InputDiceValue::~InputDiceValue()
{
}
