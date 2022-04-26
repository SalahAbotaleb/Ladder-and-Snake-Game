#include "CardNine.h"
CardNine::CardNine(const CellPosition& pos) : Card(pos) // A Constructor takes card position
{
    CardCount++;
    cardNumber = 9;
}
bool CardNine::SetPurchasePrice(int PP)
{
    if (PP > 0)
    {
        Purchase_Price = PP;
        return true;
    }
    return false;
}
bool CardNine::SetFeesPrice(int FP)
{
    if (FP > 0)
    {
        Fees_Pay = FP;
        return true;
    }
    return false;
}
int CardNine::GetPrice()
{
    return Purchase_Price;
}


void CardNine::SetOwner(Player* Owner)
{
    owner = Owner;
}



bool CardNine::isOwner(const Player* Check_Owner)
{
    return (owner == Check_Owner);
}



Card* CardNine::CopyCard()
{
    Card* copy = new CardNine(0);
    CardCount--;
    return copy;
}

Card* CardNine::PasteCard()
{
    Card* copy = new CardNine(0);
    return copy;
}

void CardNine::Load(ifstream& Infile, Object_Type obj)
{
    if (obj != card)
        return;
    Card::Load(Infile, obj);
    if (!isSet)
    {
        int price, fees;
        Infile >> price >> fees;
        SetPurchasePrice(price);
        SetFeesPrice(fees);
        isSet = 1;
    }
}

void CardNine::Save(ofstream& OutFile, Object_Type obj)
{
    if (obj != card)
        return;
    Card::Save(OutFile, obj);
    if (!issaved)
    {
        OutFile << Purchase_Price << " " << Fees_Pay;
        issaved = 1;
    }
    OutFile << endl;
}

void CardNine::reset_is_saved()
{
    issaved = 0;
}

void CardNine::reset_is_Set()
{
    isSet = 0;
}

void CardNine::ReadCardParameters(Grid* pGrid)
{
    Input* pIn = pGrid->GetInput();
    Output* pOut = pGrid->GetOutput();
    if (!isSet)
    {
        pOut->PrintMessage("Set the purchase price of this card: ");
        int Purchaseprice = pIn->GetInteger(pOut);
        while (!SetPurchasePrice(Purchaseprice))
        {
            pGrid->PrintErrorMessage("You must enter a positive value!, click any where to continue");
            pOut->PrintMessage("Re-Enter a positive value");
            Purchaseprice = pIn->GetInteger(pOut);
        }
        pOut->PrintMessage("Set the fees price number that a player must pay if he steps on the card");
        int Feesprice = pIn->GetInteger(pOut);
        while (!SetFeesPrice(Feesprice))
        {
            pGrid->PrintErrorMessage("You must enter a positive value!, click any where to continue");
            pOut->PrintMessage("Re-Enter a positive value");
            Feesprice = pIn->GetInteger(pOut);
        }
        isSet = true;
        pOut->ClearStatusBar();
    }
}

void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
    Card::Apply(pGrid, pPlayer);
    Input* pIn = pGrid->GetInput();
    Output* pOut = pGrid->GetOutput();

    if (owner == NULL)
    {
        pOut->PrintMessage("Price of this card " + to_string(Purchase_Price) + " Coins Do you want to buy this card?(Y/N)");
        string answer = pIn->GetString(pOut);
        while (answer != "n" && answer != "N" && answer != "y" && answer != "Y")
        {
            answer = pIn->GetString(pOut);
        }
        if (answer == "Y" || answer=="y")
        {
            if (pPlayer->EnoughCredit(Purchase_Price))
            {
                SetOwner(pPlayer);
                pPlayer->DeductWallet(Purchase_Price);
            }
            else
            {
                pGrid->PrintErrorMessage("You do not have enough money to buy this card, Click anywhere to continue");
            }
        }
    }
    else
    {
        if (!isOwner(pPlayer))
        {
            pGrid->PrintErrorMessage("You have to pay money for the owner of the cell, Click anywhere to continue");
            bool HaveEnoughCredit = pPlayer->EnoughCredit(Fees_Pay);
            if (HaveEnoughCredit)
            {
                owner->IncrementWallet(Fees_Pay);
            }
            else
            {
                owner->IncrementWallet(pPlayer->GetWallet());
            }
            pPlayer->DeductWallet(Fees_Pay);
        }
    }
    pOut->ClearStatusBar();
}
Player* CardNine::owner = NULL;
bool CardNine::isSet = 0;
int CardNine::Purchase_Price = 0;
int CardNine::Fees_Pay = 0;
bool CardNine::issaved = 0;
CardNine::~CardNine() {
    CardCount--;
}