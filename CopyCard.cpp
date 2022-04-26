#include "CopyCard.h"
#include "Grid.h"
#include "card.h"

CopyCard::CopyCard(ApplicationManager* pApp): Action(pApp) {}

 void CopyCard::ReadActionParameters()
 {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Click on the source cell to copy");
	Input* pIn = pGrid->GetInput();
	CopiedCell = pIn->GetCellClicked();								//getting from the user cell to copy card from 
	pOut->ClearStatusBar();
 }
 void	CopyCard:: Execute() 
 {
	 
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (!CopiedCell.IsValidCell())									//checking if the cell is valid or not
	{
		pGrid->PrintErrorMessage("invalid cell to copy! click to continue. . . . . .");
		return;														//if not valid nothing will be copied
	}
	Card* card = pGrid->CurrentCellCard(CopiedCell);				//if the CutCell valid cell it will be copied to a pointer called card
	if (card)														//checks if card pointr pionts to a card or not
	{
		card = card->CopyCard();									//creats a new card object and copies the parameters if found
	}
	else
	{																//the pointer is null
		pGrid->PrintErrorMessage("there is no card to copy");
		return;
	}
	Card* clipboard = pGrid->GetClipboard();						//creats a new pionter called pclipboard that pionts to the card in the Clipboard
	if (clipboard)
	{
		deleteClipboard(clipboard);									//if pclipboard pionts to a card it will be deleted 
	}
	pGrid->SetClipboard(card);										//then the Clipboard will be set to the NEW copied card
 }

 void CopyCard::deleteClipboard(Card* pcard)						// increases the CardCount that will decrease when deleting the clipboard
 {																	//keeps card count constant outside the grid
	 pcard->IncrementCardCount();
	 delete pcard;
 }

CopyCard::~CopyCard() {}
