#pragma once
#include "Engine/GameObject.h"
class SelectIcons :
    public GameObject
{
public:
    SelectIcons(GameObject* parent);
    ~SelectIcons();
    void Update() override;
    void Draw() override;

private:

};

