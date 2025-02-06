#pragma once
#include "Object3D.h"

class TriggerIcon;

class TriggerIcons :
    public Object3D
{
public:
    TriggerIcons(GameObject* parent);
    ~TriggerIcons();
    void Update() override;
    void Draw() override;
private:
    vector<TriggerIcon*> pTIcons_;
};

