#pragma once
#include "Icon.h"
#include<vector>

using std::vector;

class TriggerSetUIFrame :
    public Icon
{
public:
    TriggerSetUIFrame(GameObject* parent);
    ~TriggerSetUIFrame();
    void Update() override;
    void Draw() override;
private:
    string trigger;
};

