#pragma once
#include "Icon.h"
#include"TriggerSetUIFrame.h"

class TriggerSetUIFrames :
    public Icon
{
public:
    TriggerSetUIFrames(GameObject* parent);
    ~TriggerSetUIFrames();
    void Update() override;
    void Draw() override;

    auto GetpTSUIFrames() { return pTSUIFrames_; }
private:
    vector<TriggerSetUIFrame*> pTSUIFrames_;
};

