#pragma once
#include "Action.h"
#include "fstream"
#include "Grid.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
class SaveGrid :
    public Action
{
	string name ; //name of file to output to
	ofstream OutFile; //the file itself access
public:
	SaveGrid(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads SaveGrid action parameters (file name)

	virtual void Execute(); //Reads action parameters(filename)
							//saves the count of each object (ladder,snake or card)
							//saves the data of each object

	virtual ~SaveGrid(); // A Virtual Destructor
};

