#pragma once
#include "Object3D.h"
class TriggerGroup :
    public Object3D
{
public:
    TriggerGroup(GameObject* parent) : Object3D(parent){}
    ~TriggerGroup() {};
private:
};

