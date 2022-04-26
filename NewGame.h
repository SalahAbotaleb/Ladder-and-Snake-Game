#pragma once
#include "Action.h"
class NewGame: public Action
{
public:
	NewGame(ApplicationManager* pApp);				//constructor
	virtual void Execute() ;						//Restarts players' positions, wallets,turn returns to player 0
	virtual void ReadActionParameters();
	virtual ~NewGame();								//destructor
};