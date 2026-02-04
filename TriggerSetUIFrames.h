#pragma once
#include "Icon.h"
#include"TriggerSetUIFrame.h"

class TriggerSetUIFrames :
    public Icon
{
public:
    TriggerSetUIFrames(GameObject* parent);
    ~TriggerSetUIFrames();
    void Initialize() override;
    void Update() override;
    void Draw() override;

    const auto& GetpUIFrames() const{ return pUIFrames_; }

private:
    array<vector<TriggerSetUIFrame*>,static_cast<size_t>(HANDS::MAX)> pUIFrames_;
};

