#include "SwitchToDesignModeAction.h"
#include "Grid.h"

SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager *pApp) : Action(pApp)
{
}
void SwitchToDesignModeAction::ReadActionParameters() {

}
void SwitchToDesignModeAction::Execute()
{
    Grid *pGrid = pManager->GetGrid();
    Output *pOut = pGrid->GetOutput();
    pOut->CreateDesignModeToolBar(); // All you need to do to change from play to design is to change the toolbar
}
SwitchToDesignModeAction::~SwitchToDesignModeAction() {

}