#pragma once
#include "Icon.h"
class CharacterSelectUI :
    public Icon
{
public:
    CharacterSelectUI(GameObject* parent);
    ~CharacterSelectUI();
    void Initialize() override;
    void Update() override;

private:
};

