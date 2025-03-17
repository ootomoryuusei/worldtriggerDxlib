#pragma once
#include "Engine/GameObject.h"
#include"CharacterSetUIFrame.h"
#include<vector>

using std::vector;

class CharacterSetUIFrames :
    public GameObject
{
public:
    CharacterSetUIFrames(GameObject* parent);
    ~CharacterSetUIFrames();
    void Update() override;
    void Draw() override;

    auto GetpCSUIFrames() { return pCSUIFrames_; }
private:
    vector<CharacterSetUIFrame*> pCSUIFrames_;
};

