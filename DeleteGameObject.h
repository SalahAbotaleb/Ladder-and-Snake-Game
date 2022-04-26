#pragma once
#include "CellPosition.h"
#include "Action.h"
class DeleteGameObject : public Action
{
    CellPosition startPosition;

    public:
    DeleteGameObject(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~DeleteGameObject();
};

