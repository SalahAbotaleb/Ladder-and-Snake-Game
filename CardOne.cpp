#include "CardOne.h"
#include <iostream>

using namespace std;

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	CardCount++;
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}

Card* CardOne::PasteCard()
//used to take the copied card from the clipboard to grid
{
	//creating new card
	CardOne *copy = new CardOne(0);

	copy->walletAmount = walletAmount; //Sets the parameter of the card to the copy
	return copy;
}

Card* CardOne::CopyCard()//used to take a copy from the selected card to the clipboard
{
	CardOne* copy = new CardOne(0);
	CardCount--;
	/*A new card is now made for paste but it is not
	pasted yet so actual number is reduced*/

	copy->walletAmount = walletAmount; //Sets the parameter of the card to the copy

	return copy;
}

void CardOne::Load(ifstream& Infile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Load(Infile, obj);
	int val;
	Infile >> val;

	walletAmount=val;
}

void CardOne::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Save(OutFile, obj);
	OutFile << walletAmount << endl;
}

CardOne::~CardOne(void)
{
	CardCount--;
}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."

	pOut->PrintMessage("New Card1: Please enter its wallet amount...");
	int walletAmountEntered = pIn->GetInteger(pOut);
	walletAmount = walletAmountEntered;

	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();

}

void CardOne::Apply(Grid* pGrid, Player* pPlayer) {
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	pGrid->PrintErrorMessage(to_string(walletAmount) + " Coins will be deducted");
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	pPlayer->DeductWallet(walletAmount);
}
