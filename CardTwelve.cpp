#include "CardTwelve.h"
CardTwelve::CardTwelve(const CellPosition& pos):Card(pos)
{
	CardCount++; //increments the card count by 1
	cardNumber = 12;
}

void CardTwelve::ReadCardParameters(Grid* pGrid)
{
}

Card* CardTwelve::PasteCard()
{
	Card* copy = new CardTwelve(0);
	return copy;
}

Card* CardTwelve::CopyCard()
{
	Card* copy = new CardTwelve(0);
	CardCount--;
	return copy;
}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	Output *pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// checks the ownership of current player to a card 9,10 or 11 using isOwner function
	// gets the most expensive card that the current player owns
	// gets least player with coins using MinWalletPlayer function
	// moves the ownership from current player to least player
	Card::Apply(pGrid, pPlayer);

	int card_num=0;
	int maximum=0;
	int MinPlayerNum;
	Player* leastp = pGrid->MinWalletPlayer(MinPlayerNum); //getting player with least wallet value
	if (CardNine::isOwner(pPlayer))
	{
		//checking that the current player owns this station or not
		if (CardNine::GetPrice() > maximum)
		{
			//maximinzing on the stations price owned by the player  
			maximum = CardNine::GetPrice();
			card_num = 9;
		}
	}
	if (CardTen::isOwner(pPlayer))
	{
		//checking that the current player owns this station or not
		if (CardTen::GetPrice() > maximum)
		{
			maximum = CardTen::GetPrice();
			card_num = 10;
		}
	}
	if (CardEleven::isOwner(pPlayer))
	{
		//checking that the current player owns this station or not
		if (CardEleven::GetPrice() > maximum)
		{
			maximum = CardEleven::GetPrice();
			card_num = 11;
		}
	}
	if (card_num == 0)
	{
		//in case no station owned by player card_num variable won't be changed
		pGrid->PrintErrorMessage("No station ownership by player to move, click anywhere to continue");
		pOut->ClearStatusBar();
		return;
	}
	int PrevPlayerNum = pGrid->GetCurrentPlayerNum(); //Storing the index of player who's ownership will be moved
	if (pPlayer == leastp) //if the player who's ownership will be removed from his is the least amount of coins player
	{
		pGrid->PrintErrorMessage("Current player has least amount of coins therefore no ownership will be removed from this player, click to continue");
		return;
	}
	switch (card_num) // setting the ownership of the most expensive card to the least amount of coins player
	{
	case 9:
		CardNine::SetOwner(leastp);
		break;
	case 10:
		CardTen::SetOwner(leastp);
		break;
	case 11:
		CardEleven::SetOwner(leastp);
		break;
	}
	pGrid->PrintErrorMessage("OwnerShip of Card "+to_string(card_num)+" is moved from player "+to_string(PrevPlayerNum)+" to "+to_string(MinPlayerNum)+" Click to continue");
}

void CardTwelve::Save(ofstream& OutFile, Object_Type obj)
{
	if (obj != card)
		return;
	Card::Save(OutFile, obj);
	OutFile  << endl;
}

CardTwelve::~CardTwelve()
{
	CardCount--;// decrement the card count by one
}



