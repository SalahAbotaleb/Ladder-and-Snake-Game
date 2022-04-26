#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell * pCell;			// pointer to the current Cell of the player

	const int playerNum;	// the player number (from 0 to MaxPlayerCount-1)
							// player number does NOT change after construction (const.)

	int stepCount;			// step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	
	int wallet;				// player's wallet (how many coins he has -- integer)
	
	int justRolledDiceNum;	// the current dice number which is just rolled by the player
	
	int turnCount;			// a counter that starts with 0, is incremented with each dice roll
							// and reset again when reached 3
							// it is used to indicate when to move and when to add to your wallet

	int DoNotPlay;		    // DoNotPlay is a data member in Player used to indicate if the player has an 
							// extra dice roll(-1),cancelled dice roll (1) or in prision(3)
							// if DoNotPlay=0 he will play normally
	
public:

	Player(Cell * pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell * cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetWallet(int wallet);		// A setter for the wallet
	int GetWallet() const;			// a getter for the wallet

	void SetRolledDiceNum(int value); // a setter for just rolled dice
	int GetRolledDiceNum() const; // a getter for just rolled dice

	void SetDoNotPlay(int penalty);	// a setter for the DoNotPlay
	int GetDoNotPlay() ;			// a getter for the DoNotPlay

	//....

	int GetTurnCount() const;		// A getter for the turnCount
	void DeductWallet(int val); //A function that deducts ceartin amout from player if the player has sufficient money in the wallet 
	bool EnoughCredit(int val);  // functon that returns true if player wallet is greater than passed amount
	void IncrementWallet(int val); // a function that increments the walled by a given value
	///TODO: You can add setters and getters for data members here (if needed)

	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid * pGrid, int diceNumber);	// Moves the Player with the passed diceNumber 
	                                            // and Applies the Game Object's effect (if any) of the end reached cell 
	                                            // for example, if the end cell contains a ladder, take it
	
	void AppendPlayerInfo(string & playersInfo) const; // Appends player's info to the input string, 
	                                                   // for example: P0(wallet, turnCount)

};

