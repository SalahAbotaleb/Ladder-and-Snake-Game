#pragma once

#include "GameObject.h"

class Snake : public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the Snake's "Start Cell Position"

	CellPosition endCellPos; // here is the Sanke's End Cell Position
	static int SnakeCount; //a counter for the number of snakes in the grid
public:

	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a Snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the Snake by moving player to ladder's end cell
	void SetEndcell(CellPosition CP);// A setter for End Cell
	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	virtual void Load(ifstream& Infile, Object_Type obj);
	virtual void Save(ofstream& OutFile, Object_Type obj);
	static int GetObjectCount();
	virtual ~Snake(); // Virtual destructor
};

