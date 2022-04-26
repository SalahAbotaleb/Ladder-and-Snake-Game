#pragma once
#include "Action.h"
class PasteCard :	public Action
{
		CellPosition PasteCell;
		bool Can_Add;
public:

	PasteCard(ApplicationManager* pApp);					//constructor
	virtual void ReadActionParameters();					//getting from the user cell to paste card from
	virtual void Execute() ;								//getting from the Clipboard  the card to set  the chosen cell with
	~PasteCard(void);										//destructor
};
