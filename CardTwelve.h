#pragma once
#include "Card.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
class CardTwelve :
    public Card
{
    //no parameters
public:
    CardTwelve(const CellPosition& pos);
    virtual void ReadCardParameters(Grid* pGrid);// no parameters to read
    virtual Card* PasteCard();
    virtual Card* CopyCard();
    virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual void Save(ofstream& OutFile, Object_Type obj);
    ~CardTwelve();
};

