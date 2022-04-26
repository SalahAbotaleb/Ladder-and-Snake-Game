#include "CellPosition.h"

#include <iostream>
using namespace std;




CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)  to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{	
	if (v<=8 && v>=0)
	{
		vCell=v;
		return true;
	}
	else
	{
		return false;
	}
}

bool CellPosition::SetHCell(int h) 
{
	
	if (h>=0 && h<=10)
	{
		hCell=h;
		return true;
	}
	else
	{
		return false;
	}
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	if (vCell<=8 && vCell>=0 && hCell <=10 && hCell>=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	const int x=89-(11*cellPosition.VCell())+cellPosition.HCell();
	return x;
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{


	int i=0;
	bool t,t1;
	CellPosition position;

	for (int iv = 8; iv >= 0; iv--)
	{
		for (int ih = 0; ih <= 10; ih++)
		{
			i++;
			if (cellNum==i)
			{
				t=position.SetVCell(iv);
				t1=position.SetHCell(ih);
				break;
			}
			
		}
		if (cellNum == i)
		{
			break;
		}
	}	
	return position;
}

void CellPosition::AddCellNum (int addedNum)
{
	/// TODO: Implement this function as described in the .h file

	hCell+=addedNum;
		while (hCell >= 11)
		{
			hCell-=11;
			vCell--;
			if (vCell < 0)
			{
				vCell = 0;
				hCell = 10;
				break;
			}
		}
}

