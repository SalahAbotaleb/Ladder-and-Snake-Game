#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Snake.h"

Grid::Grid(Input *pIn, Output *pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut);										  // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}

// ========= Adding or Removing GameObjects to Cells =========

bool Grid::AddObjectToCell(GameObject *pNewObject) // think if any validation is needed
{
														// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell() &&pos.GetCellNum()!=1)								 // Check if valid position
	{
														// Get the previous GameObject of the Cell
		GameObject *pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false
		
						  // Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);

		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition &pos)
{
	if (pos.IsValidCell()&&CurrentCellObject(pos)) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		delete CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
	else
		PrintErrorMessage("No object in this cell to remove, click anywhere to continue");
}

void Grid::UpdatePlayerCell(Player *player, const CellPosition &newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell *newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}

// ========= Setters and Getters Functions =========

Input *Grid::GetInput() const
{
	return pIn;
}

Output *Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card *pCard) // to be used in CopyCard & CutCard
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}


Card* Grid::GetClipboard() const // to be used in PasteCard
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	if (endGame)
	{
		// print message with the winner player if ended
		PrintErrorMessage("Player " + to_string(GetCurrentPlayerNum()) + " is the winner, Click new game to restart game");
	}
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}


void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}


// ========= Other Getters =========

Player *Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder *Grid::GetNextLadder(const CellPosition &position)
{

	int startH = position.HCell();				// represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())
			{
				return CellList[i][j]->HasLadder();// returns a pointer to the ladder if there is one nearby
			}

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Player* Grid::GetNextPlayer(const CellPosition& position)
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH + 1; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a player, if yes return it
			for (int k = 0; k < 4; k++)
			{
				if (CellList[i][j]->GetCellPosition().GetCellNum() == PlayerList[k]->GetCell()->GetCellPosition().GetCellNum())
				{
					return PlayerList[k];
				}
			}

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Player* Grid::CheckCurrentCellPlayer(const CellPosition& position, int pnum)
{
	if (PlayerList[pnum]->GetCell()->GetCellPosition().GetCellNum() == position.GetCellNum()) // cehck if position given is the same as player cell position
	{
		return PlayerList[pnum];
	}
	return NULL; // not found
}

GameObject* Grid::CurrentCellObject(const CellPosition& position)
{
	//this function find whether the cell has a card or ladder or snake and return
	//pointer to this object if there is no one of those three it will return null
	GameObject *current = NULL;
	if (CellList[position.VCell()][position.HCell()]->HasCard())
	{
		current = CellList[position.VCell()][position.HCell()]->HasCard();
	}
	else if (CellList[position.VCell()][position.HCell()]->HasSnake())
	{
		current = CellList[position.VCell()][position.HCell()]->HasSnake();
	}
	else if (CellList[position.VCell()][position.HCell()]->HasLadder())
	{
		current = CellList[position.VCell()][position.HCell()]->HasLadder();
	}

	return current;
}

GameObject* Grid::CurrentCellSnake(const CellPosition& position)
{
	//this function find whether the cell has a snake and return 
	//pointer to this object if there is no snake it will return null
	GameObject* current = CellList[position.VCell()][position.HCell()]->HasSnake();

	return current;
}

GameObject* Grid::CurrentCellLadder(const CellPosition& position)
{
	//this function find whether the cell has a Ladder and return 
	//pointer to this object if there is no ladder it will return null
	GameObject* current = CellList[position.VCell()][position.HCell()]->HasLadder();

	return current;
}

Player* Grid::MinWalletPlayer(int &who) const
{
	// who is the index of least amount of coins player
	// this function returns the player who has the least amount of coins
	int min = PlayerList[0]->GetWallet();
	Player *P = PlayerList[0];
	who = 0;
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		if (PlayerList[i]->GetWallet() < min)
		{
			min = PlayerList[i]->GetWallet();
			P = PlayerList[i];
			who = i;
		}
	}
	return P;
}

int Grid::GetLadderCount()
{
	return Ladder::GetObjectCount();
}

int Grid::GetSnakeCount()
{
	return Snake::GetObjectCount();
}

int Grid::GetCardCount()
{
	return Card::GetObjectCount();
}

int Grid::GetCurrentPlayerNum() const
{
	return currPlayerNumber;
}

Card* Grid::CurrentCellCard(const CellPosition& position)
{
	//this function find whether the cell has a Card and return it
	//pointer to this object if there is no card it will return null
	Card* current = CellList[position.VCell()][position.HCell()]->HasCard();

	return current;
}

// ========= User Interface Functions =========

void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1)					  // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


void Grid::SaveAll(ofstream& OutFile, Object_Type obj)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to move from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to move from left to right
		{
			if(CellList[i][j]->HasSnake() || CellList[i][j]->HasLadder()|| CellList[i][j]->HasCard()) //checks that the cell has any object 
			(CellList[i][j]->GetGameObject())->Save(OutFile, obj);// Calls save function of cell that contains an object
		}
	}
}

void Grid::NewGame()
{
	//Delete players drawings
	
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->ClearDrawing(pOut);
	}
	//reset the players 
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;

}

void Grid::ClearGrid() //Clears all Grid objects to be able to open a new grid
{
	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}
	//reset the players 
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}