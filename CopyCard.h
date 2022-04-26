#pragma once
#include "Action.h"
class CopyCard: public Action
{
	CellPosition CopiedCell;
public:
	CopyCard(ApplicationManager* pApp);						//constructor
	virtual void ReadActionParameters();					//getting from the user cell to copied card from
	virtual void Execute() ;								// setting the Clipboard with the copied cell 
	void deleteClipboard(Card* pcard);						//function  used to free the Clipboard
	virtual ~CopyCard();									//destructor
};