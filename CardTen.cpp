#include "CardTen.h"
CardTen::CardTen(const CellPosition& pos) : Card(pos) // A Constructor takes card position
{
    CardCount++;
    cardNumber = 10;
}
bool CardTen::SetPurchasePrice(int PP)//Make sure price is positive number
{
    if (PP > 0)
    {
        Purchase_Price = PP;
        return true;
    }
    return false;
}
bool CardTen::SetFeesPrice(int FP)//Make sure price is a positive number
{
    if (FP > 0)
    {
        Fees_Pay = FP;
        return true;
    }
    return false;
}
int CardTen::GetPrice()
{
    return Purchase_Price;
}


void CardTen::SetOwner(Player* Owner)
{
    owner = Owner;
}



bool CardTen::isOwner(const Player* Check_Owner)
{
    return (owner == Check_Owner);
}



Card* CardTen::CopyCard()
{
    Card* copy = new CardTen(0);//Temporarily because i want to save it until i choose the cell i want to put it in
    CardCount--;
    return copy;
}

Card* CardTen::PasteCard()
{
    Card* copy = new CardTen(0);
    return copy;
}

void CardTen::Load(ifstream& Infile, Object_Type obj) //Input file to input the data and objects of the grid
{
    if (obj != card)
        return;
    Card::Load(Infile, obj); //Input test file if i want to load in a grid
    if (!isSet)
    {
        int price, fees;
        Infile >> price >> fees;
        SetPurchasePrice(price);
        SetFeesPrice(fees);
        isSet = 1;
    }
}

void CardTen::Save(ofstream& OutFile, Object_Type obj) //Output file that shows the data and input of the grid when we save the grid
{
    if (obj != card)
        return;
    Card::Save(OutFile, obj);
    if (!issaved)//To make sure parameters of the card is only written one time in the file
    {
        OutFile << Purchase_Price << " " << Fees_Pay;
        issaved = 1;
    }
    OutFile << endl;
}

void CardTen::reset_is_saved()//To make sure in the file that the parameters of the card is constant in the file
{
    issaved = 0;
}

void CardTen::reset_is_Set()
{
    isSet = 0; //To make sure paramaters set is constant inside the game
}

void CardTen::ReadCardParameters(Grid* pGrid)
{
    Input* pIn = pGrid->GetInput();
    Output* pOut = pGrid->GetOutput();
    if (!isSet) //Static boolean to make sure the parameters are set only one time when you call it
    {
        pOut->PrintMessage("Set the purchase price of this card: ");
        int Purchaseprice = pIn->GetInteger(pOut);
        while (!SetPurchasePrice(Purchaseprice))// Bolean set function to make sure the entered purchase price value is positive
        {
            pGrid->PrintErrorMessage("You must enter a positive value!, click any where to continue");
            pOut->PrintMessage("Re-Enter a positive value");
            Purchaseprice = pIn->GetInteger(pOut);
        }
        pOut->PrintMessage("Set the fees price number that a player must pay if he steps on the card");
        int Feesprice = pIn->GetInteger(pOut);
        while (!SetFeesPrice(Feesprice)) // Bolean set function to make sure the entered purchase price value is positive
        {
            pGrid->PrintErrorMessage("You must enter a positive value!, click any where to continue");
            pOut->PrintMessage("Re-Enter a positive value");
            Feesprice = pIn->GetInteger(pOut);
        }
        isSet = true;
        pOut->ClearStatusBar();
    }
}

void CardTen::Apply(Grid* pGrid, Player* pPlayer)
{
    Card::Apply(pGrid, pPlayer);
    Input* pIn = pGrid->GetInput();
    Output* pOut = pGrid->GetOutput();

    if (owner == NULL)//Asks first if the card has an owner
    {
        pOut->PrintMessage("Price of this card " + to_string(Purchase_Price) + " Coins Do you want to buy this card?(Y/N)");
        string answer = pIn->GetString(pOut);
        while (answer != "n" && answer != "N" && answer != "y" && answer != "Y")
        {
            answer = pIn->GetString(pOut);
        }
        if (answer == "Y" || answer=="y")
        {
            if (pPlayer->EnoughCredit(Purchase_Price))// Function to check if player has more money than purchase price or not
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
        if (!isOwner(pPlayer))// Checks if this person is the owner of the card or not to decide who will pay
        {
            pGrid->PrintErrorMessage("You have to pay money for the owner of the cell, Click anywhere to continue");
            bool HaveEnoughCredit = pPlayer->EnoughCredit(Fees_Pay); //boolean function HaveEnoughCredit to make sure that when the player pays the fees he doesn't have negative money
            if (HaveEnoughCredit)// To make sure that the owner of the card took the money of the player who paid fees not more
            {
                owner->IncrementWallet(Fees_Pay);// function to take the fees money from the player who paid 
            }
            else
            {
                owner->IncrementWallet(pPlayer->GetWallet());//Increment the owner's wallet with the money left with the player
            }
            pPlayer->DeductWallet(Fees_Pay);
        }
    }
    pOut->ClearStatusBar();
}
Player* CardTen::owner = NULL;  //WE HAVE TO initialize the static variables with a value in the cpp
bool CardTen::isSet = 0;
int CardTen::Purchase_Price = 0;
int CardTen::Fees_Pay = 0;
bool CardTen::issaved = 0;
CardTen::~CardTen() {
    CardCount--;
}