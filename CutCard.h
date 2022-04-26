#pragma once
#include "Action.h"
class CutCard:public Action
{
		CellPosition CutCell;
public:
	CutCard(ApplicationManager* pApp);						//constructor
	virtual void ReadActionParameters();					//getting from the user cell to cut card from
	virtual void Execute();									// setting the Clipboard with the cut cell 
	void deleteClipboard(Card* pcard);						//function  used to free the Clipboard
	virtual ~CutCard();										//destructor
};

