#pragma once
#include "Group.h"
class TriggerGroup :
    public Group
{
public:
    TriggerGroup(GameObject* parent) : Group(parent){}
    ~TriggerGroup() {};
private:
};

