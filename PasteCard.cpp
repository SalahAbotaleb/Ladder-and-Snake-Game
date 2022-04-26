#include "PasteCard.h"
#include "Grid.h"
#include"GameObject.h"
#include "Card.h"

PasteCard::PasteCard(ApplicationManager* pApp): Action(pApp) {
	Can_Add = 1;
}


void PasteCard:: ReadActionParameters()
{
	Grid* pGrid=pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Click on the destination cell");
	Input* pIn = pGrid->GetInput();
	PasteCell = pIn->GetCellClicked();										//getting from the user cell to cut card from
	if (!PasteCell.IsValidCell())											//check if the chosen cell vaild 
	{
		pGrid->PrintErrorMessage("invalid Position to Paste! click to continue. . . . . .");
		Can_Add = 0;
		return;
	}
																
	if (PasteCell.GetCellNum() == 1 || PasteCell.GetCellNum() == 99)		//check if the chosen cell vaild 
	{
		pGrid->PrintErrorMessage("You can't Paste a card in the First/Last cell, Click anywhere to continue");
		Can_Add = 0;
		return;
	}
	pOut->ClearStatusBar();

}


void PasteCard::Execute()
{
	ReadActionParameters();
	if (!Can_Add)
		return;
	Grid* pGrid = pManager->GetGrid();
	Card* cardp;
	if (cardp = pGrid->GetClipboard())						//check if the clipboard contains a card
	{
		if(!pGrid->CurrentCellObject(PasteCell))			//if there is no object in the cell you can paste the card
			cardp = pGrid->GetClipboard()->PasteCard();		//setting cardp with the Clipboard
	}
	else
	{														//Clipboard is NULL, so cardp will still be NULL
		pGrid->PrintErrorMessage("There is no card to paste, click anywhere to continue");
	}
		
	if (cardp)												//cardp now contains what is in the clipboard
	{
		cardp->SetCardPos(PasteCell);						//setts pos of cardp
		bool added = pGrid->AddObjectToCell(cardp);			//adds the copied card from the clipboard to the grid
		if (!added)											//check if the card is added or not
		{
			pGrid->PrintErrorMessage("Cell contains an object, can't paste ! Click to continue. . . . .");
			
		}
	}
	
 }

PasteCard::~PasteCard(){}
