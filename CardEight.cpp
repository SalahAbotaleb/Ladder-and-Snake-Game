#include "CardEight.h"


CardEight::CardEight(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	CardCount++;
	cardNumber = 8;
}
void CardEight::ReadCardParameters(Grid* pGrid)
{

	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("New CardEight: Please enter its Bail amount...");

	int AmountEntered = pIn->GetInteger(pOut);						 //getting CardEight parameter
	Bail = AmountEntered;											//setting it to the data member(bail)
	
	pOut->ClearStatusBar();

}

Card* CardEight::PasteCard()
{
	CardEight* copy = new CardEight(0);
	copy->Bail = this->Bail;
	return copy;
}

Card* CardEight::CopyCard()
{
	CardEight* copy = new CardEight(0);			 
	copy->Bail = this->Bail;					 //Sets the parameter of the card to the copy
	CardCount--;
	return copy;
}

void CardEight::Load(ifstream& Infile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Load(Infile, obj);
	int Bval;
	Infile >> Bval;
	Bail=Bval;
}
void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);									// output card number

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->PrintErrorMessage("(THE PRISION) Pay the bail or you won't be able to move for three turns.Click to continue");
	
	if (pPlayer->EnoughCredit(Bail))		//checking if the player has enough coins to paay the bail
													//if true ,he will be asked whether he would like to pay the bail or not.
	{
		pOut->PrintMessage("Would you like to pay the bail "+to_string(Bail) +" coins? enter Y/N");

		string answer = pIn->GetString(pOut);
		while (answer != "n" && answer != "N" && answer != "y" && answer != "Y")
		{
			answer = pIn->GetString(pOut);
		}

		if (answer == "y" || answer == "Y")
		{
			pPlayer->DeductWallet( Bail);				//if he answered y or Y-> his wallet will be deducted by the bail amount
		}
		else
		{
			pPlayer->SetDoNotPlay(3);					//if he answered n or N-> he won't be able to move for three turns
		}
	}
	else
	{
		pGrid->PrintErrorMessage("No enough money in the wallet! click to continue");
		pPlayer->SetDoNotPlay(3);						// if the player doesn't have enough coins he won't be able to move for three turns 
	}
	pOut->ClearStatusBar();

}

void CardEight::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Save(OutFile, obj);
	OutFile << Bail << endl;
}

CardEight::~CardEight(void)
{
	CardCount--;
}
