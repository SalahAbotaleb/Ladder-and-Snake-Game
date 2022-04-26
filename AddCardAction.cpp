#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
//including all cards files to be able to create new object of them when any card of them is required to be added


AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{
	pManager=pApp;
	// Initializes the pManager pointer of Action with the passed pointer
	Can_Add = 1; // intializes Can_Add flag with 1 because the normal case is to add 
				// but the abnormal case is 0 where there is a rule violation to grid
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	
	// 2- Read the "cardNumber" parameter and set its data member
	
	// 3- Read the "cardPosition" parameter (its cell position) and set its data member

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter the card number:");
	int cnum= pIn->GetInteger(pOut);
	while (cnum < 1 || cnum>12) //validating that the card number is between 1 and 12
	{
		pOut->PrintMessage("Wrong card number please enter card number between 1 and 12");
		cnum = pIn->GetInteger(pOut);
	}
	cardNumber = cnum;
	pOut->PrintMessage("Select card postion on the grid"); 
	CellPosition CP = pIn->GetCellClicked(); //taking from the user the cell position from the grid to set the card cell position with that cell
	if (!CP.IsValidCell()) //if the user choosed invalid position not on the grid
	{
		pGrid->PrintErrorMessage("invalid position to add card! click to continue. . . . . .");
		Can_Add = 0; // this is abnormal case where the user clicks on a postion outside the grid itself thus Can_Add flag is turned to 0
		return;
	}
	if (CP.GetCellNum() == 1 || CP.GetCellNum() == 99)
	{
		pGrid->PrintErrorMessage("You can't add a card in the First/Last cell, Click anywhere to continue");// This is abnormal case where there is rule violation (no card at first or last cell) thus Can_Add flag is turned to 0
		Can_Add = 0;
		return;
	}
	
	
	cardPosition = CP;
	pOut->ClearStatusBar();
}

void AddCardAction::Execute() 
{
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first

	ReadActionParameters();
	if (!Can_Add) //if there is abnormal case (Can_Add=0) there will be no action executed
		return;
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card * pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;
	case 2:
		pCard = new CardTwo(cardPosition);
		break;
	case 3:
		pCard = new CardThree(cardPosition);
		break;
	case 4:
		pCard = new CardFour(cardPosition);
		break;
	case 5:
		pCard = new CardFive(cardPosition); 
		break;
	case 6:
		pCard = new CardSix(cardPosition);
		break;
	case 7:
		pCard = new CardSeven(cardPosition);
		break;
	case 8:
		pCard = new CardEight(cardPosition);
		break;
	case 9:
		pCard = new CardNine(cardPosition);
		break;
	case 10:
		pCard = new CardTen(cardPosition);
		break;
	case 11:
		pCard = new CardEleven(cardPosition);
		break;
	case 12:
		pCard = new CardTwelve(cardPosition);
		break;




	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)

	if (pCard)
	{
		Grid* pGrid = pManager->GetGrid();
		if (pGrid->CurrentCellObject(cardPosition)) //if there is already an object in the cell no card will be added 
		{
			pGrid->PrintErrorMessage("Error: This cell already has an Object Can't add card! Click to continue ...");
			delete pCard;// There is no need to continue storing the card that won't be added thus it will be deleted
		}
		else
		{
			pCard->ReadCardParameters(pGrid); //In case there is no object in the cardPosition cell read the parameters and add the object to its cell
			pGrid->AddObjectToCell(pCard);
		}
		// A- We get a pointer to the Grid from the ApplicationManager

		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type

		// C- Add the card object to the GameObject of its Cell:

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
