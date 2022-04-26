#pragma once
#include "Card.h"
class CardNine :public Card
{
    static int Purchase_Price;
    static int Fees_Pay;
    static Player* owner;
    static bool isSet;
    static bool issaved;
public:
    CardNine(const CellPosition& pos);
    static int GetPrice();
    bool SetPurchasePrice(int Purchase_Price);
    //int GetFeesPrice();
    bool SetFeesPrice(int Fees_Pay);
    static void SetOwner(Player* Owner);
    static bool isOwner(const Player* Check_Owner); // checks that the send player is the owner of the card or not
   // static Player* GetOwner();
    virtual Card* CopyCard();
    virtual Card* PasteCard();
    virtual void Load(ifstream& Infile, Object_Type obj);
    virtual void Save(ofstream& OutFile, Object_Type obj);
    static  void reset_is_saved();
    static void reset_is_Set();
    virtual void ReadCardParameters(Grid* pGrid);
    virtual void Apply(Grid* pGrid, Player* pPlayer);
    virtual ~CardNine();
};


