#pragma once

#include "Card.h"

class CardFive : public Card {
  

    public:
        CardFive(const CellPosition& pos);
        virtual void ReadCardParameters(Grid* pGrid);// no parameters to read
        virtual void Apply(Grid* pGrid, Player* pPlayer);
        virtual Card* PasteCard();
        virtual Card* CopyCard();
        virtual void Save(ofstream& OutFile, Object_Type obj);
        ~CardFive();

};