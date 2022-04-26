#include "CardSix.h"

CardSix:: CardSix(const CellPosition& pos):Card(pos) // A Constructor takes card position
{
	CardCount++; //increments the card count
	cardNumber = 6;
}
 void CardSix:: ReadCardParameters(Grid* pGrid)// Reads the parameters of CardSix which is: cell position to move to
{
	 Input* pIn = pGrid->GetInput();
	 Output* pOut = pGrid->GetOutput();
	 pOut->PrintMessage("Select cell number to move player to: ");
	 CellPosition Cell_selected = pIn->GetCellClicked();
	 
	 while(!Cell_selected.IsValidCell() || Cell_selected.GetCellNum() == this->GetPosition().GetCellNum()) //if the user choosed invalid position not on the grid or the position to go to is the same card position(this will lead to infinite recursive calls)
	 {
		 pOut->PrintMessage("Re-Select Cell, invalid position to move player!");
		 Cell_selected = pIn->GetCellClicked();
	 }
	 CP = Cell_selected;
	 pOut->ClearStatusBar();
}

 Card* CardSix::PasteCard()
 {
	 CardSix* copy = new CardSix(0);
	 copy->CP = this->CP;
	 return copy;
 }
 void CardSix::Apply(Grid* pGrid, Player* pPlayer) // Applies the effect of CardSix on the passed Player
												// if there is a gameobject its effect will be implemented
 {
	 Card::Apply(pGrid, pPlayer);
	 pGrid->PrintErrorMessage("Player will go to cell " + to_string(CP.GetCellNum()) + " Click anywhere to continue!");
	 pGrid->UpdatePlayerCell(pPlayer,CP);
	 GameObject* Object = pGrid->CurrentCellObject(CP);
	 if (Object) //if the  player moved to cell contains an object
	 {
		 Object->Apply(pGrid,pPlayer); //apply the effect of this object
	 }
 }

 Card* CardSix::CopyCard()
 {
	 CardSix* copy = new CardSix(0);
	 copy->CP = this->CP;
	 CardCount--;
	 return copy;
 }

 void CardSix::Load(ifstream& Infile, Object_Type obj)
 {
	
	 if (obj != card)
		 return;
	 Card::Load(Infile, obj);
	 int cellnum;
	 Infile >> cellnum;
	 
	 CP = CellPosition(cellnum);
	 
 }

 void CardSix::Save(ofstream& OutFile, Object_Type obj)
 {
	 if (obj != card)
		 return;
	 Card::Save(OutFile, obj);
	 OutFile << CP.GetCellNum() << endl;
 }

 CardSix:: ~CardSix()
 {
	 CardCount--; //decrement the card count
  }