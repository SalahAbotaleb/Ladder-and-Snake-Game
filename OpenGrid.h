#pragma once
#include "Action.h"
#include "fstream"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"

//including  files of objects that will be dynamically allocated in open action 
class OpenGrid :
	public Action
{
	string name; //name of file to output to
	ifstream InFile; //the file itself access
public:
	OpenGrid(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads OpenGrid action parameters (file name)

	virtual void Execute(); //Reads action parameters(filename)
							//loads the count of each object (ladder,snake or card)
							//loads the data of each object

	virtual ~OpenGrid(); // A Virtual Destructor
};


