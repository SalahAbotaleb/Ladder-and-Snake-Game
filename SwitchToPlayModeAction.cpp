#include "SwitchToPlayModeAction.h"
#include "Grid.h"

SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) : Action(pApp) {}

void SwitchToPlayModeAction::ReadActionParameters() {

}
void SwitchToPlayModeAction::Execute()
{
    Grid *pGrid = pManager->GetGrid();
    Output *pOut = pGrid->GetOutput();

    pOut->CreatePlayModeToolBar();  // All you need to do to change from design to play is to change the toolbar
}
SwitchToPlayModeAction::~SwitchToPlayModeAction() {}
