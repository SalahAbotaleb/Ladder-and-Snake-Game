#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
	
	Grid* pGrid = pManager->GetGrid();

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	bool ended = pGrid->GetEndGame();
	if (ended)
	{
		return;
	}

	// Get the "current" player from pGrid
	Player* currentplayer = pManager->GetGrid()->GetCurrentPlayer();

	//Checking if the player is on card 4 or 8 ;so his dice roll is cancelled
	if (currentplayer->GetDoNotPlay() > 0)
	{
		//decreasing DoNotPlay
		currentplayer->SetDoNotPlay((currentplayer->GetDoNotPlay()) - 1);

		//calling move function to increase turnCount  and setting dice roll to zero.
		currentplayer->Move(pManager->GetGrid(), 0);

		pGrid->AdvanceCurrentPlayer();
		return;
	}
	
	//if DoNotPlay=0,the player will play normally.
	
	// 2- Generate a random number from 1 to 6 --> This step is done for you
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6;  // from 1 to 6 --> should change seed
	
	// 3- Move the currentPlayer using function Move of class player
	currentplayer->Move(pManager->GetGrid(), diceNumber);

	if (currentplayer->GetDoNotPlay() ==-1) // check if player has an extra rolldice
	{	
		currentplayer->SetDoNotPlay(0);
		
		//the player will return;thus the CurrentPlayer will not be advanced
		//(he will roll the dice again)
		return;
	}

	// 4- Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();

}

RollDiceAction::~RollDiceAction()
{
}
