#include "CutCard.h"
#include "Grid.h"
#include "Card.h"

CutCard::CutCard(ApplicationManager* pApp):Action(pApp) {}

void CutCard::ReadActionParameters()
 {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Click on the source cell to Cut");
	Input* pIn = pGrid->GetInput();
	CutCell = pIn->GetCellClicked();							//getting from the user cell to cut card from 
	pOut->ClearStatusBar();
 }
void CutCard::Execute() 
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (!CutCell.IsValidCell())									//checking if the cell is valid or not
	{
		pGrid->PrintErrorMessage("invalid cell to cut! click to continue. . . . . .");
		return;													//if not nothing will be cut
	}
	
	Card* card = pGrid->CurrentCellCard(CutCell);				//if the CutCell valid cell it will be copied to a pointer called card
	
	if (card)													//checks if card ptr pionts to a card or not
	{
		card = card->CopyCard();								//creats a new card object and copies the parameters if found
	}
	else
	{															//the pointer is null
		pGrid->PrintErrorMessage("there is no card to cut");
		return;
	}
	Card* pclipboard = pGrid->GetClipboard();					//creats a new pionter called pclipboard that pionts to the card in the Clipboard
	if (pclipboard)
	{
		deleteClipboard(pclipboard);							//if pclipboard pionts to a card it will be deleted 
	}
	pGrid->SetClipboard(card);									//then the Clipboard will be set to the NEW copied card
	pGrid->RemoveObjectFromCell(CutCell);						//and the  source card will be deleted
}
	 
void CutCard::deleteClipboard(Card* pcard)						//increases the CardCount that will decrease when deleting the clipboard
{																//keeps card count constant outside the grid
	pcard->IncrementCardCount();
	delete pcard;
}
CutCard::~CutCard(){}
