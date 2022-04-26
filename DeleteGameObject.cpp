#include "DeleteGameObject.h"
#include "Grid.h"

DeleteGameObject::DeleteGameObject(ApplicationManager *pApp) : Action(pApp)
{
}

void DeleteGameObject::ReadActionParameters()
{
    Grid *pGrid = pManager->GetGrid();
    Output *pOut = pGrid->GetOutput();
    Input *pIn = pGrid->GetInput();
    pOut->PrintMessage("Delete game object: Select the game object you want to delete. If it is a ladder or a snake, please click on its starting cell...");
    startPosition = pIn->GetCellClicked();// Set the start position of the object with the cell clicked by the user
    pOut->ClearStatusBar();
};

void DeleteGameObject::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    ReadActionParameters();
        pGrid->RemoveObjectFromCell(startPosition);// Remove object from the cell the user clicked on

}

DeleteGameObject::~DeleteGameObject() {

}