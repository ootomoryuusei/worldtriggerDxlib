#pragma once
#include "Engine/GameObject.h"
#include"TriggerSetUI.h"
#include<vector>

using std::vector;

class TriggerSetUIs :
    public GameObject
{
public:
    TriggerSetUIs(GameObject* parent);
    ~TriggerSetUIs();
    void Update() override;
    void Draw() override;

    auto GetpTSUIFrames() { return pTSUIs; }
private:
    vector<TriggerSetUI*> pTSUIs;

};

